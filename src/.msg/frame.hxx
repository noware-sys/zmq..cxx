#pragma once
/*
#include <zmq.hpp>

namespace zmq
{
*/
	class frame
	// TODO
	// handle nullptr case
	{
		public:
			frame (void);
			frame (const frame &);
			frame (const zframe_t *);
			frame (const message_t &);
			frame (const zmq_msg_t *);
			frame (const std::string &);
			
			virtual ~frame (void);
			
			virtual operator const zframe_t * (void) const;
			virtual operator const message_t & (void) const;
			virtual operator message_t & (void);
			virtual operator const zmq_msg_t * (void) const;
			virtual operator const std::string (void) const;
			
			virtual const frame & operator = (const frame &);
			virtual const zframe_t * operator = (const zframe_t *);
			virtual const message_t & operator = (const message_t &);
			virtual const zmq_msg_t * operator = (const zmq_msg_t *);
			virtual const std::string & operator = (const std::string &);
			
			virtual const bool operator == (const frame &) const;
			virtual const bool operator == (const zframe_t *) const;
			virtual const bool operator == (const message_t &) const;
			virtual const bool operator == (const zmq_msg_t *) const;
			virtual const bool operator == (const std::string &) const;
			
			virtual const bool operator != (const frame &) const;
			virtual const bool operator != (const zframe_t *) const;
			virtual const bool operator != (const message_t &) const;
			virtual const bool operator != (const zmq_msg_t *) const;
			virtual const bool operator != (const std::string &) const;
			
			static void free (void * /* data*/, void * /* hint*/);
		//protected:
			message_t data;
		protected:
			//virtual const bool fin (void);
			//virtual const bool init (void);
			
	};
//}
