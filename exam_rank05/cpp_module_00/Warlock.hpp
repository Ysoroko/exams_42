/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:50:33 by ysoroko           #+#    #+#             */
/*   Updated: 2021/12/21 12:09:36 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARLOCK_HPP
# define WARLOCK_HPP

#include <iostream>

class Warlock
{
	public:
		// Constructors + Destructors
		Warlock(std::string name, std::string title);
		~Warlock();

		// Getters:
		const std::string	getName( void ) const;
		const std::string	getTitle( void ) const;

		// Setters:
		void	setTitle( const std::string & title );

		// Introduce:
		void	introduce() const;

	private:
		// COPLIEN FORM:
		// ---------------------------
		// Assignment operator
		Warlock & operator=(const Warlock & rhs);

		// Constructor
		Warlock();

		// Copy constructor
		// ---------------------------

		std::string _name;
		std::string _title;
};

#endif