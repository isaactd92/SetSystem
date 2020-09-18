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

#ifndef INCLUDED_SETSYSTEM_SETSYSTEM_IMPL_H
#define INCLUDED_SETSYSTEM_SETSYSTEM_IMPL_H

#include <SetSystem/SetSystem.h>
#include <SetSystem/ArgProcessor/ArgProcessor.h>

namespace gr {
  namespace SetSystem {

    class SetSystem_impl : public SetSystem
    {
     private:
      const char* c_path_file;
      const std::string c_mac_block;
      int c_port_block;
      const std::string c_ip_host;

     public:
      SetSystem_impl(const char* path_file, const std::string mac_block, int port_block, const std::string ip_host);
      ~SetSystem_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace SetSystem
} // namespace gr

#endif /* INCLUDED_SETSYSTEM_SETSYSTEM_IMPL_H */

