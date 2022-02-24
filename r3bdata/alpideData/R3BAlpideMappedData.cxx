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

// -----------------------------------------------------------------------
// -----            R3BAlpideMappedData source file                  -----
// -----------------------------------------------------------------------

#include "R3BAlpideMappedData.h"

R3BAlpideMappedData::R3BAlpideMappedData()
    : fDetId(0)
    , fChip(0)
    , fReg(0)
    , fAds(0)
    , fChip(0)
    , fRow(0)
    , fCol(0)
{
}

R3BAlpideMappedData::R3BAlpideMappedData(UShort_t detId, UShort_t chip, UShort_t reg, UShort_t col, UShort_t ads)
    : fDetId(detId)
    , fChip(chip)
    , fReg(reg)
    , fAds(ads)
    , fChip(chip)
    , fRow(row)
    , fCol(col)
{
}

ClassImp(R3BAlpideMappedData);
