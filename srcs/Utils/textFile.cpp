/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   TextFile.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/06 16:29:56 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/08/06 16:36:25 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

namespace Utils
{
	void openTextFile(std::fstream &file, std::string income)
	{
		file.open(income);
		if (!file)
			throw openFileError("Error: failed to open filepath: ", income);

	}

	void	closeTextFile(std::fstream &file)
	{
		file.close();
	}
}