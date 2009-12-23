/**********************************************************************
 *                                                                    *
 * Voreen - The Volume Rendering Engine                               *
 *                                                                    *
 * Copyright (C) 2005-2009 Visualization and Computer Graphics Group, *
 * Department of Computer Science, University of Muenster, Germany.   *
 * <http://viscg.uni-muenster.de>                                     *
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

#include "voreen/core/vis/processors/image/imageprocessor.h"

namespace voreen {

const std::string ImageProcessor::shadeTexUnit_ = "shadeTexUnit";
const std::string ImageProcessor::depthTexUnit_ = "depthTexUnit";

ImageProcessor::ImageProcessor(const std::string& shaderFilename)
    : RenderProcessor()
    , program_(0)
    , shaderFilename_(shaderFilename)
{
    std::vector<std::string> units;
    units.push_back(depthTexUnit_);
    units.push_back(shadeTexUnit_);
    tm_.registerUnits(units);
}

ImageProcessor::~ImageProcessor() {
    if (program_)
        ShdrMgr.dispose(program_);
}

void ImageProcessor::initialize() throw (VoreenException) {

    RenderProcessor::initialize();

    if (!shaderFilename_.empty()) {
        program_ = ShdrMgr.loadSeparate("pp_identity.vert", shaderFilename_ + ".frag", generateHeader(), false, false);
        if (program_) {
            invalidate(Processor::INVALID_PROGRAM);
            if (getInvalidationLevel() >= Processor::INVALID_PROGRAM)
                compile();
        }
        if (!program_) {
            LERROR("Failed to load shaders!");
            initialized_ = false;
            throw VoreenException(getClassName() + ": Failed to load shaders!");
        }
        else {
            program_->deactivate();
        }
    }
    else
        program_ = 0;

}

void ImageProcessor::compile() {
    if (program_)
        program_->rebuild();
}

} // voreen namespace
