
/*
 *=============================================================================
 * Copyright (C) 2008 Alon Zakai ('Kripken') kripkensteiner@gmail.com
 *
 * This file is part of the Intensity Engine project,
 *    http://www.intensityengine.com
 *
 * The Intensity Engine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * The Intensity Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with the Intensity Engine.  If not, see
 *     http://www.gnu.org/licenses/
 *     http://www.gnu.org/licenses/agpl-3.0.html
 *=============================================================================
 */


struct fpsserver;

//! The fpsserver class is critical in Sauerbraten, but it is accessible only to its interior
//! members, which are generated by including them in. Instead, we allow interfacing with that
//! class to our exterior systems through this interface.

struct FPSServerInterface
{
    //! The instace of the fpsserver that we work with (a singleton)
    static fpsserver* fpsserverInstance;

    //! Gets the number of clients connected to the server. The range 0..this number is valid for clients, BUT not all may be
    //! full - check for NULLs. This is how Sauer works, entries are in the same place as their clientnumber
    static int getNumClients();

    //! Gets the username of a connected client (modifiable)
    static std::string& getUsername(int clientNumber);

    //! Gets the uniqueId of a connected client (modifiable)
    static int&         getUniqueId(int clientNumber);

    //! Changes the active map
    static void         changeMap(std::string name);

    static void cleanWorldState(ENetPacket *packet);
};

