// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2017.
//
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS.
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// --------------------------------------------------------------------------
// $Maintainer: Hannes Roest $
// $Authors: Hannes Roest $
// --------------------------------------------------------------------------

#pragma once

// Interfaces
#include <OpenMS/ANALYSIS/OPENSWATH/OPENSWATHALGO/DATAACCESS/TransitionExperiment.h>

#include <OpenMS/KERNEL/FeatureMap.h>

#include <fstream>

namespace OpenMS
{

  /**
   * @brief Class to write out an OpenSwath TSV output (mProphet input)
   *
   * The class can take a FeatureMap and create a set of string from it
   * suitable for output to tsv using the prepareLine function.
   *
   * These lines can also be directly written to a file using writeLines
   *
   */
  class OPENMS_DLLAPI OpenSwathTSVWriter
  {
    std::ofstream ofs;
    String input_filename_;
    bool doWrite_;
    bool use_ms1_traces_;
    bool sonar_;
    bool enable_uis_scoring_;

  public:

    OpenSwathTSVWriter(String output_filename, 
                       String input_filename = "inputfile",
                       bool ms1_scores = false, 
                       bool sonar = false, 
                       bool uis_scores = false);

    bool isActive();

    /**
     * @brief Initializes file by writing TSV header
     *
     */
    void writeHeader();

    /**
     * @brief Prepare a single line (feature) for output
     *
     * The result can be flushed to disk using writeLines (either line by line
     * or after collecting several lines).
     *
     * @param pep The compound (peptide/metabolite) used for extraction
     * @param transition The transition used for extraction 
     * @param output The feature map containing all features (each feature will generate one entry in the output)
     * @param id The transition group identifier (peptide/metabolite id)
     *
     * @returns A string to be written using writeLines
     *
     */
    String prepareLine(const OpenSwath::LightCompound& pep,
        const OpenSwath::LightTransition * transition,
        const FeatureMap& output, const String id);

    /**
     * @brief Write data to disk
     *
     * Takes a set of pre-prepared data statements from prepareLine and flushes them to disk
     * 
     * @param to_output Statements generated by prepareLine to be written to a file
     *
     * @note Only call inside an OpenMP critical section
     *
     */
    void writeLines(std::vector<String> to_output);

  };

}


