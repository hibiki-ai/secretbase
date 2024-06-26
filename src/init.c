// Copyright (C) 2024 Hibiki AI Limited <info@hibiki-ai.com>
//
// This file is part of secretbase.
//
// secretbase is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// secretbase is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// secretbase. If not, see <https://www.gnu.org/licenses/>.

// secretbase - package level registrations ------------------------------------

#include "secret.h"

static const R_CallMethodDef callMethods[] = {
  {"secretbase_base64enc", (DL_FUNC) &secretbase_base64enc, 2},
  {"secretbase_base64dec", (DL_FUNC) &secretbase_base64dec, 2},
  {"secretbase_sha3", (DL_FUNC) &secretbase_sha3, 3},
  {"secretbase_sha3_file", (DL_FUNC) &secretbase_sha3_file, 3},
  {"secretbase_shake256", (DL_FUNC) &secretbase_shake256, 3},
  {"secretbase_shake256_file", (DL_FUNC) &secretbase_shake256_file, 3},
  {"secretbase_keccak", (DL_FUNC) &secretbase_keccak, 3},
  {"secretbase_keccak_file", (DL_FUNC) &secretbase_keccak_file, 3},
  {"secretbase_sha256", (DL_FUNC) &secretbase_sha256, 3},
  {"secretbase_sha256_file", (DL_FUNC) &secretbase_sha256_file, 3},
  {"secretbase_siphash13", (DL_FUNC) &secretbase_siphash13, 3},
  {"secretbase_siphash13_file", (DL_FUNC) &secretbase_siphash13_file, 3},
  {NULL, NULL, 0}
};

void attribute_visible R_init_secretbase(DllInfo* dll) {
  R_registerRoutines(dll, NULL, callMethods, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  R_forceSymbols(dll, TRUE);
}
