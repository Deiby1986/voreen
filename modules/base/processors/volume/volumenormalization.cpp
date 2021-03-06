/**********************************************************************
 *                                                                    *
 * Voreen - The Volume Rendering Engine                               *
 *                                                                    *
 * Created between 2005 and 2012 by The Voreen Team                   *
 * as listed in CREDITS.TXT <http://www.voreen.org>                   *
 *                                                                    *
 * This file is part of the Voreen software package. Voreen is free   *
 * software: you can redistribute it and/or modify it under the terms *
 * of the GNU General Public License version 2 as published by the    *
 * Free Software Foundation.                                          *
 *                                                                    *
 * Voreen is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the       *
 * GNU General Public License for more details.                       *
 *                                                                    *
 * You should have received a copy of the GNU General Public License  *
 * in the file "LICENSE.txt" along with this program.                 *
 * If not, see <http://www.gnu.org/licenses/>.                        *
 *                                                                    *
 * The authors reserve all rights not expressly granted herein. For   *
 * non-commercial academic use see the license exception specified in *
 * the file "LICENSE-academic.txt". To get information about          *
 * commercial licensing please contact the authors.                   *
 *                                                                    *
 **********************************************************************/

#include "modules/base/processors/volume/volumenormalization.h"

#include "voreen/core/datastructures/volume/operators/volumeoperatornormalize.h"

namespace voreen {

VolumeNormalization::VolumeNormalization()
    : CachingVolumeProcessor()
    , inport_(Port::INPORT, "volume.inport")
    , outport_(Port::OUTPORT, "volume.outport", true)
{
    addPort(inport_);
    addPort(outport_);
}

void VolumeNormalization::process() {
    const VolumeHandleBase* inputVolume = inport_.getData();
    VolumeHandle* outputVolume = inputVolume->clone();

    VolumeHandle* t = VolumeOperatorNormalize::APPLY_OP(outputVolume);
    delete outputVolume;
    outputVolume = t;

    //std::cout << outputVolume->getRepresentation<Volume>()->min() << " || " << outputVolume->getRepresentation<Volume>()->max() << std::endl;

    if (outputVolume)
        outport_.setData(outputVolume);
    else
        outport_.setData(0);
}

} // namespace
