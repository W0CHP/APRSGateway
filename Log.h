/*
 *   Copyright (C) 2015,2016,2020,2022,2023 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#if !defined(LOG_H)
#define	LOG_H

#include <string>

#include <nlohmann/json.hpp>

#define	LogDebug(fmt, ...)	Log(1U, fmt, ##__VA_ARGS__)
#define	LogMessage(fmt, ...)	Log(2U, fmt, ##__VA_ARGS__)
#define	LogInfo(fmt, ...)	Log(3U, fmt, ##__VA_ARGS__)
#define	LogWarning(fmt, ...)	Log(4U, fmt, ##__VA_ARGS__)
#define	LogError(fmt, ...)	Log(5U, fmt, ##__VA_ARGS__)
#define	LogFatal(fmt, ...)	Log(6U, fmt, ##__VA_ARGS__)

extern void Log(unsigned int level, const char* fmt, ...);

extern void LogInitialise(unsigned int displayLevel, unsigned int mqttLevel);
extern void LogFinalise();

extern void WriteJSON(const std::string& topLevel, nlohmann::json& json, bool retain);

// Structured link-state event, mirroring the "link" Kind DMRGateway/
// YSFGateway/DStarGateway already publish -- APRSGateway never had one
// before (only a bare start/stop "status" string). action is one of
// "linking"/"unlinked"/"failed"; reason is only meaningful for "failed"
// (see APRSWriterThread.cpp for the actual values) and can be left empty
// otherwise. A free function, not a CAPRSGateway member, because
// CAPRSWriterThread -- a separate class that owns the actual APRS-IS
// socket -- is what needs to call this directly, the same reasoning
// DStarGateway's writeJSONLinking/Unlinked/Failed already established.
extern void writeJSONLink(const std::string& action, const std::string& reason);

#endif
