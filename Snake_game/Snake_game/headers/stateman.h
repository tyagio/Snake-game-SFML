#ifndef STATEMAN_H
#define STATEMAN_H

#include "state.h"

////////////////////////////////////////////////////////////
/// \brief state manager 
///
/// This class mantains and allows changes to the statestack
///
////////////////////////////////////////////////////////////
class stateman
{
private:
	////////////////////////////////////////////////////////////
	/// \brief state stack
	///
	/// state stack inside which game states mantained 
	////////////////////////////////////////////////////////////
	std::stack<std::unique_ptr<state>> m_statestack;

	////////////////////////////////////////////////////////////
	/// \brief buffer to input new state 
	///
	/// stores unique ptr given by user until it is given to 
	/// state stack in processstatechange function
	////////////////////////////////////////////////////////////
	std::unique_ptr<state> m_newstate;

	////////////////////////////////////////////////////////////
	/// \brief bool for adding state
	///
	////////////////////////////////////////////////////////////
	bool m_add;

	////////////////////////////////////////////////////////////
	/// \brief bool to specify type of addition
	///
	/// if true then addeed state will replace current,
	/// if false simply added on top of stack
	////////////////////////////////////////////////////////////
	bool m_replace;

	////////////////////////////////////////////////////////////
	/// \brief bool for removing top state
	///
	/// if true then current state is to be removed
	////////////////////////////////////////////////////////////
	bool m_remove;

public:
	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	////////////////////////////////////////////////////////////
	stateman();

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	////////////////////////////////////////////////////////////
	~stateman();
	
	////////////////////////////////////////////////////////////
	/// \brief Adds new state
	///
	/// if replace is true then given state replaces current 
	/// state, else if false then it is added on top of 
	/// current state  of stack,state beneath added one is 
	/// paused in every case
	/// 
	/// \param toAdd unique ptr of state to be added
	/// \param replace specifies if it should replace current state 
	////////////////////////////////////////////////////////////
	void Add(std::unique_ptr<state> toAdd, bool replace = false);

	////////////////////////////////////////////////////////////
	/// \brief removes current state
	///
	///  removes the current state and starts the one beneath it
	////////////////////////////////////////////////////////////
	void Popcurrent();

	////////////////////////////////////////////////////////////
	/// \brief processes all the state changes 
	///
	/// implements all the state changes which have happened 
	/// inside Add and Popcurrent functions
	///
	////////////////////////////////////////////////////////////
	void ProcessStatechange();

	////////////////////////////////////////////////////////////
	/// \brief returns refernce to current state
	///
	////////////////////////////////////////////////////////////
	std::unique_ptr<state>& Getcurrent();


	bool is_empty();
};

#endif