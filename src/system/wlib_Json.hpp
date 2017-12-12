////////////////////////////////////////
//(c) 2016  white    wlib_Json.hpp
////////////////////////////////////////

// FINALIZED
// version 1.0 (@2016_10_07)

/*

### HOW TO USE ###

# The simplest usage

	Json test_json("JSON TEXT.......");

	double value = test_json["hoge"]...["hage"].num();
	std::string str = test_json["hoge"]...["hage"].str();

Very Very Easy!!!!
*/

#pragma once

#ifndef WLIB_JSON_HPP
#define WLIB_JSON_HPP

#include <string>
#include "picojson.hpp"
#include <memory>

namespace wlib {
class Json {
public:
	/** Constructor. Input the json text and decode.
	 * @param json_str Json text.
	 * @param err_dump Error text will set this variable. No error, and err_dump is empty. If the err_dump is nullptr, no error dump, but get it from getError function.
	 */
	Json(const std::string & json_str);

	/** Destructor.
	 */
	virtual ~Json();

	/** Access the json object in key.
	 * @param key the key string.
	 * @returns wlib::Json Instance.
	 */
	Json operator[](const std::string & key);

	/** Access the json array in index
	 * @param index the index of the json array.
	 * @returns wlib::Json Instance
	 */
	Json operator[](const std::size_t index);

	/** Get the value as double value.
	 * @returns the value.
	 */
	double num(const double default_value = 0.0);

	/** Get the value as string.
	* @returns the string.
	*/
	std::string str(const std::string default_str = "");


	/** Get the value as boolean.
	* @returns the flags.
	*/
	bool is(const bool default_value = false);

	/** Get the size of array.
	* @returns the size of array.
	*/
	std::size_t size();


	///////////////////////
	// Error Accessor
	///////////////////////

	/** Get the data whether some error has occured or not.
	 * @returns true means some error has occured.
	 */
	bool isError(void) const;

	/** Get the error dump.
	 * @returns the error dump text.
	 */
	std::string getError(void) const;

private:
	Json();
	Json(const picojson::value & v, const std::shared_ptr<std::string> & shp_err_str, const std::shared_ptr<bool> & shp_first_flag);
	Json(const Json & copy);

	template<typename T> T get(T default_object);


	////////////////////////
	// Member Variable
	////////////////////////
	std::shared_ptr<std::string> shp_err_str;
	std::shared_ptr<bool> shp_first_flag;

	picojson::value json_value;

};

};

//INLINE FUNCTIONS
inline bool wlib::Json::isError(void) const{
	if (this->shp_err_str) {
		return !this->shp_err_str->empty();
	}
	return false;
}

#endif