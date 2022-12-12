/******************************************************************************
 *   Copyright (C) 2019 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2019 Members of R3B Collaboration                          *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************/

#include "R3BCalifaCMSBoost.h"
#include "TClonesArray.h"
#include "TMath.h"

#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

#include "R3BLogger.h"

#include "Math/Vector3D.h"
#include "Math/Vector4D.h"
#include "Math/Boost.h"
#include "R3BCalifaHitData.h"

using namespace ROOT::Math;

R3BCalifaCMSBoost::R3BCalifaCMSBoost()
    : FairTask("R3B CALIFA boost into CMS")
{

}

R3BCalifaCMSBoost::~R3BCalifaCMSBoost()
{
    R3BLOG(DEBUG1, "");
    if (fCalifaHitData)
        delete fCalifaHitData;
}


InitStatus R3BCalifaCMSBoost::Init()
{
    R3BLOG(INFO, "");
    assert(!fCalifaHitData); // in case someone calls Init() twice.

    FairRootManager* ioManager = FairRootManager::Instance();
    R3BLOG_IF(fatal, !ioManager, "FairRootManager not found");

    fCalifaHitData = (TClonesArray*)ioManager->GetObject("CalifaHitData");

    // We do not init a new outputarray but instead adding fields to the loaded TClonesArray
    // and fill it with the task.
    return kSUCCESS;
}


// -----   Public method Exec   --------------------------------------------
void R3BCalifaCMSBoost::Exec(Option_t* opt)
{
    Int_t nHits = fCalifaHitData->GetEntries(); // GetEntriesFast() ???
    if(!nHits)
    {
        return;
    }
    
    for (Int_t i = 0; i < nHits; i++)
    {
        auto hitData = (R3BCalifaHitData*)(fCalifaHitData->At(i));

        // Philipp said it is not expensive to init the variables and it is more 
        // readable.
        Double_t energy = hitData->GetEnergy();
        Double_t phi = hitData->GetPhi();
        Double_t theta = hitData->GetTheta();

        /**
         * This 4-vector is based on the LorentzVector class, the successor of TLorentzVector
         * Goal is to boost GAMMAS (mass=0) into the CM frame (Doppler correction) with the help
         * of the angular information, provided by CALIFA.
         */
        PxPyPzMVector p(energy * sin(theta) * cos(phi), 
        energy * sin(phi) * sin(theta), 
        energy * cos(theta), 
        energy);
        
        hitData->fBeta = TVector3(0, 0, 0.7); // TODO: Fetch from separate class
        Boost gammaBoost(-hitData->fBeta);
        auto pdash = gammaBoost(p);

        // Filling the additional fields in R3BCalifaHitData with the boosted values
        hitData->fEnCMS = pdash.E();
        hitData->fDirCM.SetXYZ(pdash.Px(),pdash.Py(),pdash.Pz());
    }

    return;
}


ClassImp(R3BCalifaCMSBoost);
