/* -*- c++ -*- */
/* 
 * Copyright 2020 gr-SetSystem author.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */


#ifndef INCLUDED_SETSYSTEM_SETSYSTEM_H
#define INCLUDED_SETSYSTEM_SETSYSTEM_H

#include <SetSystem/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace SetSystem {

    /*!
     * \brief <+description of block+>
     * \ingroup SetSystem
     *
     */
    class SETSYSTEM_API SetSystem : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<SetSystem> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of SetSystem::SetSystem.
       *
       * To avoid accidental use of raw pointers, SetSystem::SetSystem's
       * constructor is in a private implementation
       * class. SetSystem::SetSystem::make is the public interface for
       * creating new instances.
       */
      static sptr make(const char* path_file, const std::string mac_block, int port_block, const std::string ip_host);
    };

  } // namespace SetSystem
} // namespace gr

#endif /* INCLUDED_SETSYSTEM_SETSYSTEM_H */

