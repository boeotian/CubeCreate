
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

var myArray = [1, 2, "3", null];

assert( "typeof serializeJSON(myArray) === 'string'" );
assert( "typeof(evalJSON(serializeJSON(myArray))[1]) === 'number'" );
assert( "typeof(evalJSON(serializeJSON(myArray))[2]) === 'string'" );
assert( "objEqual(evalJSON(serializeJSON(myArray)), myArray)" );

// We have the following change to stock MochiKit:
//var me=arguments.callee;
//var _f5;
//if(o === undefined) return "[UNDEFINED]"; // Kripken: Added this!
//if(typeof (o.__json__)=="function"){
//_f5=o.__json__();

