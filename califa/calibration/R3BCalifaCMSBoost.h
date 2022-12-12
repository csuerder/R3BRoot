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

#ifndef R3BCALIFACMSBOOST_H
#define R3BCALIFACMSBOOST_H 1

#include "FairTask.h"
#include "R3BCalifaHitData.h"
#include "TMath.h"

#include <TVector3.h>

class TClonesArray;

class R3BCalifaCMSBoost : public FairTask
{

  public:
    /** Default constructor
     **/
    R3BCalifaCMSBoost();

    /** Destructor **/
    virtual ~R3BCalifaCMSBoost();

    /** Virtual method Exec **/
    /**
     * Idea from Philipp Klenze. The override method makes sure that there is no typo in the calass and that 
     * the return type is the same. It needs ClassDefOverride()
    */
    virtual void Exec(Option_t* opt) override;

    /** Accessor to select online mode **/
    void SetOnline(Bool_t option) { fOnline = option; };

    /** Virtual method Init **/
    virtual InitStatus Init() override;


  private:

    // Instead of setting the used objects in the construcor of the class they are
    // initialized here
    TClonesArray* fCalifaHitData{nullptr};
    Bool_t fOnline{false}; // Selector for online data storage

    ClassDefOverride(R3BCalifaCMSBoost, 2); // Important for override
};

#endif /* R3BCALIFACMSBOOST_H */
