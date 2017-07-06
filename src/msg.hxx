#pragma once

#include <map>

#include <zmq.hpp>
#include <czmq.h>

#include <noware/nr.hxx>

//#include "frame.hxx"

#include ".msg/incl.hxx"

namespace zmq
{
	// A multipart message
	
	class msg
	{
		public:
			#include ".msg/.hxx"
			
			msg (void);
			msg (const msg &);
			msg (const zmsg_t *);
			msg (const frame &);
			msg (const zframe_t *);
			msg (const message_t &);
			msg (const zmq_msg_t *);
			msg (const std::string &);
			
			virtual ~msg (void);
			
			virtual operator const zmsg_t * (void) const;
			virtual operator const frame & (void) const;
			virtual operator const zframe_t * (void) const;
			virtual operator const message_t & (void) const;
			virtual operator message_t & (void);
			virtual operator const zmq_msg_t * (void) const;
			virtual operator const std::string (void) const;
			
			virtual const msg & operator = (const msg &);
			virtual const zmsg_t * operator = (const zmsg_t *);
			virtual const frame & operator = (const frame &);
			virtual const zframe_t * operator = (const zframe_t *);
			virtual const message_t & operator = (const message_t &);
			virtual const zmq_msg_t * operator = (const zmq_msg_t *);
			virtual const std::string & operator = (const std::string &);
			
			virtual const bool operator == (const msg &) const;
			virtual const bool operator == (const zmsg_t *) const;
			virtual const bool operator == (const frame &) const;
			virtual const bool operator == (const zframe_t *) const;
			virtual const bool operator == (const message_t &) const;
			virtual const bool operator == (const zmq_msg_t *) const;
			virtual const bool operator == (const std::string &) const;
			
			virtual const bool is_empty () const;
			virtual const bool is_full () const;
			
			virtual const bool first (frame &) const;
			virtual const bool last (frame &) const;
			
			virtual const frame first (void) const;
			virtual const frame last (void) const;
			
			virtual const bool first_rm (void);
			virtual const bool last_rm (void);
			
			virtual const bool first_rm (frame &);
			virtual const bool last_rm (frame &);
			
			virtual const bool append (const frame &);
			virtual const bool prepend (const frame &);
			
			// frame
			
			//virtual const bool operator != (const msg &) const;
			//virtual const bool operator != (const zmsg_t &) const;
			//virtual const bool operator != (const frame &) const;
		//protected:
			//std::map <noware::nr/* key type*/, frame/* value type*/> data;
			std::map <unsigned int/* key type*/, frame/* value type*/> data;
			//zmsg_t data;
		protected:
			virtual const bool fin (void);
			virtual const bool init (void);
			
			virtual const bool first_space_clear (void);
			virtual const bool first_space_fill (void);
	};
	
	//typedef noware::list <message_t, noware::nr> msg;
	//typedef std::map <noware::nr/* key type*/, frame/* value type*/> msg;
	//template <typename value_t = var, typename key_t = var>
	//using msg = std::map <noware::nr, frame>;
}
