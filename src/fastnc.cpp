// Software in the Sustain Ecosystem are Released Under Terms of Apache Software License
// This research has been supported by funding from the US National Science Foundation’s CSSI program through awards 1931363, 1931324, 1931335, and 1931283.
// The project is a joint effort involving Colorado State University, Arizona State University, the University of California-Irvine, and the University of Maryland – Baltimore County.
// All re-distributions of the software must also include this information.
//
// TERMS AND CONDITIONS FOR USE, REPRODUCTION, AND DISTRIBUTION
//
//     1. Definitions.
//
//     "License" shall mean the terms and conditions for use, reproduction, and distribution as defined by Sections 1 through 9 of this document.
//
//     "Licensor" shall mean the copyright owner or entity authorized by the copyright owner that is granting the License.
//
//     "Legal Entity" shall mean the union of the acting entity and all other entities that control, are controlled by, or are under common control with that entity. For the purposes of this definition, "control" means (i) the power, direct or indirect, to cause the direction or management of such entity, whether by contract or otherwise, or (ii) ownership of fifty percent (50%) or more of the outstanding shares, or (iii) beneficial ownership of such entity.
//
//     "You" (or "Your") shall mean an individual or Legal Entity exercising permissions granted by this License.
//
//     "Source" form shall mean the preferred form for making modifications, including but not limited to software source code, documentation source, and configuration files.
//
//     "Object" form shall mean any form resulting from mechanical transformation or translation of a Source form, including but not limited to compiled object code, generated documentation, and conversions to other media types.
//
//     "Work"shall mean the work of authorship, whether in Source or Object form, made available under the License, as indicated by a copyright notice that is included in or attached to the work (an example is provided in the Appendix below).
//
//     "Derivative Works"shall mean any work, whether in Source or Object form, that is based on (or derived from) the Work and for which the editorial revisions, annotations, elaborations, or other modifications represent, as a whole, an original work of authorship. For the purposes of this License, Derivative Works shall not include works that remain separable from, or merely link (or bind by name) to the interfaces of, the Work and Derivative Works thereof.
//
//     "Contribution"shall mean any work of authorship, including the original version of the Work and any modifications or additions to that Work or Derivative Works thereof, that is intentionally submitted to Licensor for inclusion in the Work by the copyright owner or by an individual or Legal Entity authorized to submit on behalf of the copyright owner. For the purposes of this definition, "submitted" means any form of electronic, verbal, or written communication sent to the Licensor or its representatives, including but not limited to communication on electronic mailing lists, source code control systems, and issue tracking systems that are managed by, or on behalf of, the Licensor for the purpose of discussing and improving the Work, but excluding communication that is conspicuously marked or otherwise designated in writing by the copyright owner as "Not a Contribution."
//
//     "Contributor"shall mean Licensor and any individual or Legal Entity on behalf of whom a Contribution has been received by Licensor and subsequently incorporated within the Work.
//
//     2. Grant of Copyright License.
//
//     Subject to the terms and conditions of this License, each Contributor hereby grants to You a perpetual, worldwide, non-exclusive, no-charge, royalty-free, irrevocable copyright license to reproduce, prepare Derivative Works of, publicly display, publicly perform, sublicense, and distribute the Work and such Derivative Works in Source or Object form.
//
//     3. Grant of Patent License.
//
//     Subject to the terms and conditions of this License, each Contributor hereby grants to You a perpetual, worldwide, non-exclusive, no-charge, royalty-free, irrevocable (except as stated in this section) patent license to make, have made, use, offer to sell, sell, import, and otherwise transfer the Work, where such license applies only to those patent claims licensable by such Contributor that are necessarily infringed by their Contribution(s) alone or by combination of their Contribution(s) with the Work to which such Contribution(s) was submitted. If You institute patent litigation against any entity (including a cross-claim or counterclaim in a lawsuit) alleging that the Work or a Contribution incorporated within the Work constitutes direct or contributory patent infringement, then any patent licenses granted to You under this License for that Work shall terminate as of the date such litigation is filed.
//
//     4. Redistribution.
//
//     You may reproduce and distribute copies of the Work or Derivative Works thereof in any medium, with or without modifications, and in Source or Object form, provided that You meet the following conditions:
//         1. You must give any other recipients of the Work or Derivative Works a copy of this License; and
//         2. You must cause any modified files to carry prominent notices stating that You changed the files; and
//         3. You must retain, in the Source form of any Derivative Works that You distribute, all copyright, patent, trademark, and attribution notices from the Source form of the Work, excluding those notices that do not pertain to any part of the Derivative Works; and
//         4. If the Work includes a "NOTICE" text file as part of its distribution, then any Derivative Works that You distribute must include a readable copy of the attribution notices contained within such NOTICE file, excluding those notices that do not pertain to any part of the Derivative Works, in at least one of the following places: within a NOTICE text file distributed as part of the Derivative Works; within the Source form or documentation, if provided along with the Derivative Works; or, within a display generated by the Derivative Works, if and wherever such third-party notices normally appear. The contents of the NOTICE file are for informational purposes only and do not modify the License. You may add Your own attribution notices within Derivative Works that You distribute, alongside or as an addendum to the NOTICE text from the Work, provided that such additional attribution notices cannot be construed as modifying the License.
//
//     You may add Your own copyright statement to Your modifications and may provide additional or different license terms and conditions for use, reproduction, or distribution of Your modifications, or for any such Derivative Works as a whole, provided Your use, reproduction, and distribution of the Work otherwise complies with the conditions stated in this License.
//
//     5. Submission of Contributions.
//
//     Unless You explicitly state otherwise, any Contribution intentionally submitted for inclusion in the Work by You to the Licensor shall be under the terms and conditions of this License, without any additional terms or conditions. Notwithstanding the above, nothing herein shall supersede or modify the terms of any separate license agreement you may have executed with Licensor regarding such Contributions.
//
//     6. Trademarks.
//
//     This License does not grant permission to use the trade names, trademarks, service marks, or product names of the Licensor, except as required for reasonable and customary use in describing the origin of the Work and reproducing the content of the NOTICE file.
//
//     7. Disclaimer of Warranty
//
//     Unless required by applicable law or agreed to in writing, Licensor provides the Work (and each Contributor provides its Contributions) on an “AS IS” BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied, including, without limitation, any warranties or conditions of TITLE, NON-INFRINGEMENT, MERCHANTABILITY, or FITNESS FOR A PARTICULAR PURPOSE. You are solely responsible for determining the appropriateness of using or redistributing the Work and assume any risks associated with Your exercise of permissions under this License.
//
//     8. Limitation of Liability
//
//     In no event and under no legal theory, whether in tort (including negligence), contract, or otherwise, unless required by applicable law (such as deliberate and grossly negligent acts) or agreed to in writing, shall any Contributor be liable to You for damages, including any direct, indirect, special, incidental, or consequential damages of any character arising as a result of this License or out of the use or inability to use the Work (including but not limited to damages for loss of goodwill, work stoppage, computer failure or malfunction, or any and all other commercial damages or losses), even if such Contributor has been advised of the possibility of such damages.
//
// END OF TERMS AND CONDITIONS

#include <algorithm>
#include <utility>
#include "fastnc.h"
#include "commonmutex.h"
#include "cfdims.h"

std::mutex common_mutex;

FastNcFile::FastNcFile(std::string _filename, std::vector<std::string> _basic_dims, std::set<std::string> _wanted_variables)
    : filename(std::move(_filename)), basic_dims(std::move(_basic_dims)) {
    std::lock_guard<std::mutex> nc_lock(common_mutex);
    netCDF::NcFile nc_file(filename, netCDF::NcFile::read);

    for (const std::string& dim : basic_dims) {
        cache(nc_file, dim);
    }

    if (_wanted_variables.empty()) {
        _wanted_variables = get_nonbasic_vars(nc_file);
    }

    for (const auto &var : _wanted_variables) {
        cache(nc_file, var);
    }

    verify_consistent_var_sizes();

    wanted_variables = std::move(_wanted_variables);
}

FastNcFile::FastNcFile(std::string _filename, const std::set<std::string> &_wanted_variables)
    : FastNcFile(std::move(_filename), CF_DEFAULT_BASIC_DIMS, _wanted_variables) { }

FastNcFile::FastNcFile(std::string _filename)
    : FastNcFile(std::move(_filename), {}) { }

FastNcFile::~FastNcFile() {
    for (auto &pair : data) {
        delete[] pair.second;
    }
}

void FastNcFile::cache(const netCDF::NcFile &nc_file, const std::string &variable) {
    netCDF::NcVar nc_var = nc_file.getVar(variable);

    double sentinel_value = get_attribute<double>(nc_var, "missing_value");
    if (sentinel_value == std::numeric_limits<double>::min()) {
        sentinel_value = get_attribute<double>(nc_var, "_FillValue");
    }

    size_t size = get_data_size(nc_var);
    std::string standard_name = get_attribute<std::string>(nc_var, "standard_name");
    double scale_factor = get_attribute<double>(nc_var, "scale_factor");
    double offset = get_attribute<double>(nc_var, "add_offset");
    std::vector<std::string> dimension_order = get_ordered_dims_for(nc_var);

    data[variable] = new double[size];
    metadata[variable] = { sentinel_value, size, standard_name, scale_factor, offset, dimension_order};

    nc_var.getVar(data[variable]);
}

size_t FastNcFile::get_data_size(const netCDF::NcVar &nc_var) {
    size_t size = 1;
    for (int i = 0; i < nc_var.getDimCount(); i++) {
        size *= nc_var.getDim(i).getSize();
    }

    return size;
}

std::set<std::string> FastNcFile::get_nonbasic_vars(const netCDF::NcFile &nc_file) {
    std::set<std::string> vars;
    for (const auto &var : nc_file.getVars()) {
        if (find(basic_dims.begin(), basic_dims.end(), var.first) == basic_dims.end() &&
            find(CF_STANDARD_DIMS.begin(), CF_STANDARD_DIMS.end(), var.first) == CF_STANDARD_DIMS.end()) {
            vars.insert(var.first);
        }
    }

    return vars;
}

double FastNcFile::get_dim_value(const std::string &dim, size_t index) {
    return data[dim][index];
}

double *FastNcFile::get_all_data(const std::string &variable) {
    return data[variable];
}

DimValues FastNcFile::get_dim_values(size_t _1d_index, const std::string &var) {
    DimValues values{};

    std::vector<size_t> indices = _1d_index_to_dim_indices(_1d_index, var);

    for (size_t i = 0; i < indices.size(); i++) {
        size_t inverted_i = indices.size() - i - 1;
        std::string dim = metadata[var].dimension_order[inverted_i];
        values[dim] = get_dim_value(dim, indices[i]);
    }

    return values;
}

std::vector<size_t> FastNcFile::_1d_index_to_dim_indices(size_t _1d_index, const std::string &var) {
    std::vector<size_t> indices;
    std::vector<std::string> order = metadata[var].dimension_order;
    for (auto it = order.rbegin(); it != order.rend(); it++) {
        auto dim = *it;
        size_t dim_size = metadata[dim].length;
        indices.push_back(_1d_index % dim_size);
        _1d_index /= dim_size;
    }

    return indices;
}

const std::map<std::string, VariableMetadata> &FastNcFile::get_metadata_view() const {
    return metadata;
}

void FastNcFile::verify_consistent_var_sizes() {
    std::vector<std::pair<std::string, VariableMetadata>> no_basic_metadata(metadata.size());
    auto basic_dim_filter = [this](const decltype(metadata)::value_type &pair) {
        return std::find(basic_dims.begin(), basic_dims.end(), pair.first) == basic_dims.end();
    };

    auto copy_stop = std::copy_if(metadata.begin(), metadata.end(), no_basic_metadata.begin(), basic_dim_filter);
    no_basic_metadata.resize(std::distance(no_basic_metadata.begin(), copy_stop));

    size_t current = no_basic_metadata.begin()->second.length;
    for (const auto &pair : no_basic_metadata) {
        if (current != pair.second.length) {
            throw std::runtime_error("Sizes of variables in file are inconsistent: please specify variable list");
        }
        current = pair.second.length;
    }
}

std::vector<std::string> FastNcFile::get_ordered_dims_for(const netCDF::NcVar &nc_var) {
    std::vector<std::string> dims;
    for (const auto &nc_dim : nc_var.getDims()) {
        dims.push_back(nc_dim.getName());
    }
    return dims;
}
