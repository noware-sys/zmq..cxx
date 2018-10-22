#pragma once

#include "msg.hxx"
#include ".msg/incl.cxx"
#include ".msg/.cxx"

#include <zmq.hpp>
#include <czmq.h>
//#include <zmsg.c>

#include <cln/nr.cxx>

#include <string>
#include <iostream>
//#include "frame.cxx"

//#pragma once

//#include "frame.hxx"

zmq::msg::msg (void)
{
	init ();
	//*this = "";
}

zmq::msg::msg (const msg & other)
{
	init ();
	*this = other;
}

zmq::msg::msg (const zmsg_t * other)
{
	init ();
	*this = other;
}

zmq::msg::msg (const frame & other)
{
	init ();
	*this = other;
}

zmq::msg::msg (const zframe_t * other)
{
	init ();
	*this = other;
}

zmq::msg::msg (const message_t & other)
{
	init ();
	*this = other;
}

zmq::msg::msg (const zmq_msg_t * other)
{
	init ();
	*this = other;
}

zmq::msg::msg (const std::string & other)
{
	init ();
	*this = other;
}

zmq::msg::~msg (void)
{
	termin ();
}

const bool zmq::msg::termin (void)
{
}

const bool zmq::msg::init (void)
{
}

zmq::msg::operator const zmsg_t * (void) const
{
	zmsg_t * msg;
	zframe_t * frame_p;
	zframe_t ** frame_pp;
	
	msg = zmsg_new ();
	//frame = zframe_new_empty ();
	
	//for (const std::pair <cln::nr, zmq::msg::frame> & _frame : data)
	for (const std::pair <unsigned int, /*zmq::msg::*/frame> & _frame : data)
	{
		//zframe_reset (_frame, );
		//frame_p = (zframe_t *) _frame.second;
		frame_p = _frame.second.operator const zframe_t * ();
		frame_pp = &frame_p;
		
		//assert (zframe_is (*frame_pp));
		//assert ((*frame_pp) -> tag == ZFRAME_TAG);
		
		zmsg_append (msg, frame_pp);
	}
	
	return msg;
}

zmq::msg::operator const frame & (void) const
{
	return data [0];
}

zmq::msg::operator const zframe_t * (void) const
{
	return data [0];
}

zmq::msg::operator const message_t & (void) const
{
	//return data [1].operator const message_t & ();
	return data [0];
}

zmq::msg::operator message_t & (void)
{
	//return data [1].operator message_t & ();
	return data [0];
}

zmq::msg::operator const zmq_msg_t * (void) const
{
	return data [0];
}

zmq::msg::operator const std::string (void) const
{
	return data [0];
}

const zmq::msg & zmq::msg::operator = (const msg & other)
{
	data = other.data;
	
	return other;
}

const zmsg_t * zmq::msg::operator = (const zmsg_t * other)
{
	zframe_t * frm;
	//cln::nr ndx;
	unsigned int ndx;
	
	data.clear ();
	frm = zmsg_first (other);
	ndx = 0;
	while (frm != nullptr)
	{
		// This makes a copy of the frame.
		data [ndx] = frm;
		
		//zframe_destroy (&f);
		
		frm = zmsg_next (other);
		++ndx;
	}
	
	return other;
}

const zmq::msg::frame & zmq::msg::operator = (const frame & other)
{
	data.clear ();
	data [0] = other;
	
	return other;
}

const zframe_t * zmq::msg::operator = (const zframe_t * other)
{
	data.clear ();
	data [0] = other;
	
	return other;
}

const zmq::message_t & zmq::msg::operator = (const message_t & other)
{
	data.clear ();
	data [0] = other;
	
	return other;
}

const zmq_msg_t * zmq::msg::operator = (const zmq_msg_t * other)
{
	data.clear ();
	data [0] = other;
	
	return other;
}

const std::string & zmq::msg::operator = (const std::string & other)
{
	//std::cerr << "zmq::msg::operator=(str)::" << std::endl;
	
	data.clear ();
	data [0] = other;
	
	//std::cerr << std::string (data [1]) << std::endl;
	
	return other;
}

const bool zmq::msg::operator == (const msg & other) const
{
	return data == other.data;
}

const bool zmq::msg::operator == (const zmsg_t * other) const
{
	return *this == msg (other);
}

const bool zmq::msg::operator == (const frame & other) const
{
	return *this == msg (other);
}

const bool zmq::msg::operator == (const zframe_t * other) const
{
	return *this == msg (other);
}

const bool zmq::msg::operator == (const message_t & other) const
{
	return *this == msg (other);
}

const bool zmq::msg::operator == (const zmq_msg_t * other) const
{
	return *this == msg (other);
}

const bool zmq::msg::operator == (const std::string & other) const
{
	return *this == msg (other);
}

const bool zmq::msg::operator != (const msg & other) const
{
	return !(data == other.data);
}

const bool zmq::msg::operator != (const zmsg_t * other) const
{
	return !(*this == other);
}

const bool zmq::msg::operator != (const frame & other) const
{
	return !(*this == other);
}

const bool zmq::msg::operator != (const zframe_t * other) const
{
	return !(*this == other);
}

const bool zmq::msg::operator != (const message_t & other) const
{
	return !(*this == other);
}

const bool zmq::msg::operator != (const zmq_msg_t * other) const
{
	return !(*this == other);
}

const bool zmq::msg::operator != (const std::string & other) const
{
	return !(*this == other);
}

const bool zmq::msg::is_empty () const
{
	return data.empty ();
}

const bool zmq::msg::is_full () const
{
	return false;
}

const bool zmq::msg::first (frame & f) const
{
	if (is_empty ())
		return false;
	
	f = data [0];
	
	return true;
}

const bool zmq::msg::last (frame & f) const
{
	if (is_empty ())
		return false;
	
	f = data [data.size () - 1];
	
	return true;
}

const zmq::msg::frame zmq::msg::first (void) const
{
	frame f;
	
	if (!is_empty ())
		f = data [0];
	
	return f;
}

const zmq::msg::frame zmq::msg::last (void) const
{
	frame f;
	
	if (!is_empty ())
		f = data [data.size () - 1];
	
	return f;
}

const bool zmq::msg::first_rm (void)
{
	if (is_empty ())
		return true;
	
	data.erase (0);
	
	if (!first_space_fill ())
		return false;
	
	//data.erase (1);
	
	return true;
}

const bool zmq::msg::last_rm (void)
{
	if (is_empty ())
		return true;
	
	data.erase (data.size ());
	
	return true;
}

const bool zmq::msg::first_rm (frame & f)
{
	if (is_empty ())
		return true;
	
	f = data [0];
	data.erase (0);
	
	if (!first_space_fill ())
		return false;
	
	return true;
}

const bool zmq::msg::last_rm (frame & f)
{
	if (is_empty ())
		return true;
	
	f = data [data.size () - 1];
	data.erase (data.size () - 1);
	
	return true;
}

const bool zmq::msg::append (const frame & f)
{
	if (is_full ())
		return false;
	
	data [data.size ()] = f;
	
	return true;
}

const bool zmq::msg::prepend (const frame & f)
{
	if (is_full ())
		return false;
	
	if (!first_space_clear ())
		return false;
	
	data [0] = f;
	//data.insert_or_assign (1, f);
	
	//for (const std::pair <cln::nr, frame> & element : data)
	//{
	//	std::cerr << "zmq::msg::prepend()::data[" << element.first << "]==\"" << std::string (element.second) << "\"" << std::endl;
	//}
	dump ();
	
	return true;
}

const bool zmq::msg::first_space_clear (void)
{
	std::cerr << "zmq::msg::first_clear_space()::called" << std::endl;
	if (is_empty ())
	{
		// nothing to do
		std::cerr << "zmq::msg::first_clear_space()::is_empty()==[true]" << std::endl;
		return true;
	}
	std::cerr << "zmq::msg::first_clear_space()::is_empty()==[false]" << std::endl;
	
	if (is_full ())
	{
		std::cerr << "zmq::msg::first_clear_space()::is_full()==[true]" << std::endl;
		// no more space
		return false;
	}
	std::cerr << "zmq::msg::first_clear_space()::is_full()==[false]" << std::endl;
	
	std::map <int unsigned, frame> result;
	//std::string key;
	//std::string key_tmp;
	//frame tmp;
	
	for (std::pair <int unsigned, frame> const & element : data)
	{
		//key = element.first;
		//element.first = "key_tmp";
		
		result [element.first + 1] = element.second;
		//result [element.first + 1] = data [element.first];
		//tmp = element.second;
		//data.erase (element.first);
		//data [element.first + 1];
	}
	//data.erase (0);
	data.clear ();
	/*
	for (std::pair <unsigned int, frame> const & element : result)
	{
		//key = element.first;
		//element.first = "key_tmp";
		
		data [element.first] = element.second;
		//data [element.first] = result [element.first];
		//tmp = element.second;
		//data.erase (element.first);
		//data [element.first + 1];
	}
	*/
	data = result;
	result.clear ();
	
	dump ();
	
	//std::swap (data, result);
	//data = result
	
	std::cerr << "zmq::msg::first_clear_space()::return" << std::endl;
	return true;
}

const bool zmq::msg::first_space_fill (void)
{
	if (is_empty ())
		// nothing to do
		return true;
	
	//if (is_full ())
	//	// no more space
	//	return false;
	
	std::map <unsigned int, frame> result;
	//std::string key;
	//std::string key_tmp;
	//frame tmp;
	
	for (const std::pair <unsigned int, frame> & element : data)
	{
		//key = element.first;
		//element.first = "key_tmp";
		
		result [element.first - 1] = element.second;
		//tmp = element.second;
		//data.erase (element.first);
		//data [element.first + 1];
	}
	//data.erase (0);
	data.clear ();
	//result.erase (0);
	for (const std::pair <unsigned int, frame> & element : result)
	{
		//key = element.first;
		//element.first = "key_tmp";
		
		data [element.first] = element.second;
		//tmp = element.second;
		//data.erase (element.first);
		//data [element.first + 1];
	}
	//result.clear ();
	
	//std::swap (data, result);
	//data = result
	
	return true;
}


void zmq::msg::dump (void) const
{
	std::string str;
	int unsigned size;
	
	std::cerr << std::hex;
	std::cerr << std::setw (2);
	//std::cerr << std::setfill ('0');
	std::cerr << std::noshowbase;
	
	for (std::pair <int unsigned, frame> const & element : data)
	{
		str = std::string (element.second);
		size = str.size ();
		
		//key = element.first;
		//element.first = "key_tmp";
		
		//data [element.first] = element.second;
		//tmp = element.second;
		//data.erase (element.first);
		//data [element.first + 1];
		
		//std::cerr << "zmq::msg::dump()::data[" << element.first << "]==\"" << std::string (element.second) << "\"" << std::endl;
		//std::cerr << std::setfill('0') << std::setw(2) << std::hex << (unsigned int) element.second.data ();
		
		std::cerr << '[' << element.first << ']';
		std::cerr << '=';
		
		std::cerr << '[';
		for (int unsigned i = 0; i < size; ++i)
		{
			std::cerr << std::setfill ('0') << (int unsigned) str [i];
		}
		std::cerr << ']';
		std::cerr << std::endl;
	}
	
	std::cerr << std::dec;
	std::cerr << std::setw (0);
	std::cerr << std::setfill ('\0');
}

/*
zmq::msg::frame & zmq::msg::operator [] (int unsigned const & key)
{
	return data [key];
}
*/
