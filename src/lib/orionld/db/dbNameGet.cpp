/*
*
* Copyright 2019 Telefonica Investigacion y Desarrollo, S.A.U
*
* This file is part of Orion Context Broker.
*
* Orion Context Broker is free software: you can redistribute it and/or
* modify it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* Orion Context Broker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero
* General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Orion Context Broker. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by this license please contact with
* iot_support at tid dot es
*
* Author: Ken Zangelin
*/
#include "logMsg/logMsg.h"                                       // LM_*
#include "logMsg/traceLevels.h"                                  // Lmt*

#include "orionld/common/orionldState.h"                         // orionldState, dbName
#include "orionld/db/dbNameGet.h"                                // Own interface
  


// ----------------------------------------------------------------------------
//
// dbNameGet -
//
int dbNameGet(char* path, int pathLen)
{
  int used;

  strncpy(path, dbName, pathLen);
  used = strlen(dbName);  // Can be faster - orionldState can keep this constant

  if ((multitenancy == true) && (orionldState.tenant != NULL))
  {
    LM_TMP(("DB: tenant: %s", orionldState.tenant));
    path[used] = '-';
    ++used;
    strncat(&path[used], orionldState.tenant, pathLen - used);
    used += strlen(orionldState.tenant);
  }

  if (used > pathLen)
  {
    LM_E(("Internal Error (database name is too long)"));
    return -1;
  }

  LM_TMP(("DB: database name: %s", path));
  return 0;
}