 /* Copyright 2010 q66 <quaker66@gmail.com>
 * 
 * The file is part of CubeCreate project, which is licensed under MIT license.
 * The license file should be bundled with your CubeCreate distribution.
 * 
 */

/**
 * @mainpage Engine Variables
 * 
 * @author q66 <quaker66@gmail.com>
 * @date 2010
 */

/**
 * @defgroup Lua_Engine_Group LuaEngine
 *
 * @{
 */

#ifdef __clang__
# define __clang_block __block
# undef __block
#endif

# include <iostream>
# include <map>
# include <set>

// there is shared_ptr in graph's branch, remove
#include <boost/shared_ptr.hpp>
// there is anytype in graph's branch too
#include <boost/any.hpp>

#define anyint boost::any_cast<int>
#define anydouble boost::any_cast<double>
#define anystring boost::any_cast<std::string>

#ifdef __clang__
# define __block __clang_block
# undef __clang_block
#endif

#ifdef __clang__
# define _cb_ ^
# define _lambda_ ^
#else
# define _cb_ *
# define _lambda_ []
#endif

/**
 * @class EngineVariable
 * Basic class representing engine variable.
 */
class EngineVariable
{
public:
    /**
     * @brief Integer variable constructor.
     * @param vname Name of future variable.
     * @param minvi Minimal value of variable.
     * @param curvi Default value of variable.
     * @param maxvi Maximal value of variable.
     * @param cb Callback to be run on value change. Optional. Can be either lambda or standard function.
     * @param persist Sets if the future variable is going to be persistent through script engine restarts.
     * 
     * Construct an integer variable.
     */
	EngineVariable(
		const std::string& vname,
		int minvi,
		int curvi,
		int maxvi,
		void (_cb_ cb)(int, int, int, int) = NULL,
		bool persist = false
	);
    /**
     * @brief Double variable constructor.
     * @param vname Name of future variable.
     * @param minvf Minimal value of variable.
     * @param curvf Default value of variable.
     * @param maxvf Maximal value of variable.
     * @param cb Callback to be run on value change. Optional. Can be either lambda or standard function.
     * @param persist Sets if the future variable is going to be persistent through script engine restarts.
     * 
     * Construct a double variable.
     */
	EngineVariable(
		const std::string& vname,
		double minvf,
		double curvf,
		double maxvf,
		void (_cb_ cb)(double, double, double, double) = NULL,
		bool persist = false
	);
    /**
     * @brief String variable constructor.
     * @param vname Name of future variable.
     * @param curvs Default value of variable.
     * @param cb Callback to be run on value change. Optional. Can be either lambda or standard function.
     * @param persist Sets if the future variable is going to be persistent through script engine restarts.
     * 
     * Construct a string variable. Doesn't have min, max because it makes no sense for strings.
     */
	EngineVariable(
		const std::string& vname,
		const std::string& curvs,
		void (_cb_ cb)(const std::string&, const std::string&) = NULL,
		bool persist = false
	);
    /**
     * @brief Get a name of the variable.
     * @return A string containing name of the variable.
     * 
     * Get a name of the variable.
     */
	std::string getName();
    /**
     * @brief Get a type of the variable.
     * @return A string containing type of the variable.
     * 
     * Get a type of the variable.
     */
	std::string getType();
    /**
     * @brief Get a string value of the variable.
     * @return A string containing value of the variable.
     * 
     * Get a string value of the variable.
     */
	std::string getString();
    /**
     * @brief Get an integer value of the variable.
     * @return An integer containing value of the variable.
     * 
     * Get an integer value of the variable.
     */
	int getInteger();
    /**
     * @brief Get a double value of the variable.
     * @return A double containing value of the variable.
     * 
     * Get a double value of the variable.
     */
	double getDouble();
    /**
     * @brief Set an integer value of the variable.
     * @param val The value itself.
     * @param luaSync Defaults to true, optional, if true, syncing with Lua will be done after change.
     * 
     * Sets an integer value of the variable.
     */
	void set(int val, bool luaSync = true, bool forceCB = false);
    /**
     * @brief Set a double value of the variable.
     * @param val The value itself.
     * @param luaSync Defaults to true, optional, if true, syncing with Lua will be done after change.
     * 
     * Sets a double value of the variable.
     */
	void set(double val, bool luaSync = true, bool forceCB = false);
    /**
     * @brief Set a string value of the variable.
     * @param val The value itself.
     * @param luaSync Defaults to true, optional, if true, syncing with Lua will be done after change.
     * 
     * Sets a string value of the variable.
     */
	void set(std::string val, bool luaSync = true, bool forceCB = false);
    /**
     * @brief Gets if the variable is persistent.
     * @return If persistent, then true, otherwise false.
     * 
     * Gets if the variable is persistent.
     */
	bool isPersistent();
    /**
     * @brief Gets if the variable is read only.
     * @return If read only, then true, otherwise false.
     * 
     * Gets if the variable is read only (only from Lua though!).
     */
	bool isReadOnly();
    /**
     * @brief Registers integer Lua variable based on C++ representation it's ran for.
     * 
     * Registers integer Lua variable based on C++ representation it's ran for.
     */
	void registerLuaIVAR();
    /**
     * @brief Registers double Lua variable based on C++ representation it's ran for.
     * 
     * Registers integer Lua variable based on C++ representation it's ran for.
     */
	void registerLuaFVAR();
    /**
     * @brief Registers string Lua variable based on C++ representation it's ran for.
     * 
     * Registers integer Lua variable based on C++ representation it's ran for.
     */
	void registerLuaSVAR();
private:
	// this one can call a callback if set; it also does a value sync with Lua which can call lua callback.
	void callCB(bool luaSync, bool forceCB);

	// is the var persistent?
	bool persistent;
	// has the var a C++ callback?
	bool hasCB;
	// var name
	std::string name;
	// var type
	std::string type;
	// is readonly (only from lua, C++ is writable)?
	bool readOnly;

	// anytypes storing the values
	boost::any prev;
	boost::any minv;
	boost::any curv;
	boost::any maxv;

	// union storing the callback (for memory save)
	union
	{
		void (_cb_ intCB)(int, int, int, int);
		void (_cb_ doubleCB)(double, double, double, double);
		void (_cb_ stringCB)(const std::string&, const std::string&);
	};
};

/// Typedef shared_ptr of EngineVariable to EngineVariablePtr for simpler syntax.
typedef boost::shared_ptr<EngineVariable> EngineVariablePtr;
/// Typedef map of string and variable ptr to EVMap for simpler syntax.
typedef std::map<std::string, EngineVariablePtr> EVMap;
/// Typedef pair of string and variable ptr to EVPair for simpler syntax.
typedef std::pair<std::string, EngineVariablePtr> EVPair;

/**
 * @class EngineVariables
 * Class representing storage for EngineVariable(Ptr)'s
 */
class EngineVariables
{
public:
    /**
     * @brief Register a variable into storage.
     * @param name Name of the variable.
     * @param var EngineVariablePtr representing the variable.
     * 
     * Register a variable into storage.
     */
	static void reg(const std::string& name, EngineVariablePtr var);
    /**
     * @brief Clear the storage (but save persistents in special map)
     * 
     * Clear the storage (but save persistents in special map)
     */
	static void clear();
    /**
     * @brief Fill the storage from persistents and register all other vars.
     * 
     * Fill the storage from persistents and register all other vars. Doesn't fill Lua.
     */
	static void fill();
    /**
     * @brief Fill Lua script engine with variables from storage.
     * 
     * Fill Lua script engine with variables from storage.
     */
	static void fillLua();
    /**
     * @brief Fill storage from persistents.
     * 
     * Fill storage from persistents.
     */
	static void fillFromPersistent();
    /**
     * @brief Sync an integer value from Lua.
     * @param name Name of the variable.
     * @param value Integer value to sync.
     * 
     * When setting value in Lua, this is called to change state in C++.
     */
	static void syncFromLua(const std::string& name, int value);
    /**
     * @brief Sync a double value from Lua.
     * @param name Name of the variable.
     * @param value Double value to sync.
     * 
     * When setting value in Lua, this is called to change state in C++.
     */
	static void syncFromLua(const std::string& name, double value);
    /**
     * @brief Sync a string value from Lua.
     * @param name Name of the variable.
     * @param value String value to sync.
     * 
     * When setting value in Lua, this is called to change state in C++.
     */
	static void syncFromLua(const std::string& name, const std::string& value);
    /**
     * @brief Get the EngineVariablePtr for specified name.
     * @param name Name of the variable to get shared ptr for.
     * @return The EngineVariablePtr for specified name.
     * 
     * Changes done with the returned ptr reflect in storage too, i.e.
     * @code
     * EngineVariables::get("blah").get()->set(5);
     * int woot = EngineVariables::get("blah").get()->getInteger();
     * @endcode
     */
	static EngineVariablePtr& get(const std::string& name);
private:
	// storage and persistent storage. First one is cleared, second one is cleared just on persistent values transfer to standard storage.
	static EVMap storage;
	static EVMap persistentStorage; // used just on clear() - persistent vars get moved here
};

/**
 * @def REGVAR
 * @brief Macro for simplifying variable registration.
 * @param name Name of the variable to register.
 * @param ... This differs for every variable.
 * 
 * For integer variable, you pass three integer values in addition to name (min, cur, max) and optionally a callback
 * (void closure or void) and boolean setting persistency - true means persistent. For double variable, it's the same
 * except passed values are doubles. Callback for integer and double variables takes 4 integer/double arguments
 * (min, max, prev, cur). For string variable, you pass just cur value (no min, max),
 * and callback accepts just two arguments (prev and cur).
 */
#define REGVAR(name, ...) EngineVariables::reg(name, EngineVariablePtr(new EngineVariable(name, __VA_ARGS__)))

/**
 * @def ICB
 * @brief Macro for making lambda callback creation easier.
 * @param code The code used as body of lambda function.
 * 
 * This creates a lambda function callback for integer variables, letting @p code get minv, maxv, prev and curv values.
 * @code
 * REGVAR("foo", 0, 1, 2, ICB({ foo }));
 * @endcode
 */
#define ICB(code) _lambda_(_UNUSED_ int minv, _UNUSED_ int maxv, _UNUSED_ int prev, _UNUSED_ int curv) code

/**
 * @def FCB
 * @brief Macro for making lambda callback creation easier.
 * @param code The code used as body of lambda function.
 * 
 * This creates a lambda function callback for double variables, letting @p code get minv, maxv, prev and curv values.
 * @code
 * REGVAR("foo", 0.1, 1.3, 5.1, FCB({ foo }));
 * @endcode
 */
#define FCB(code) _lambda_(_UNUSED_ double minv, _UNUSED_ double maxv, _UNUSED_ double prev, _UNUSED_ double curv) code

/**
 * @def SCB
 * @brief Macro for making lambda callback creation easier.
 * @param code The code used as body of lambda function.
 * 
 * This creates a lambda function callback for string variables, letting @p code get prev and curv values.
 * @code
 * REGVAR("foo", "bar", SCB({ foo }));
 * @endcode
 */
#define SCB(code) _lambda_(_UNUSED_ const std::string& prev, _UNUSED_ const std::string& curv) code

/**
 * @def GETIV
 * @brief Macro for making getting variable value easier.
 * @param name Name of the variable to get.
 * 
 * Gets value of variable of name @p name as integer.
 * @code
 * int i = GETIV(foo);
 * @endcode
 */
#define GETIV(name) EngineVariables::get(#name).get()->getInteger()

/**
 * @def GETFV
 * @brief Macro for making getting variable value easier.
 * @param name Name of the variable to get.
 * 
 * Gets value of variable of name @p name as double.
 * @code
 * double d = GETFV(foo);
 * @endcode
 */
#define GETFV(name) EngineVariables::get(#name).get()->getDouble()

/**
 * @def GETSV
 * @brief Macro for making getting variable value easier.
 * @param name Name of the variable to get.
 * 
 * Gets value of variable of name @p name as string.
 * @code
 * std::string s = GETSV(foo);
 * @endcode
 */
#define GETSV(name) EngineVariables::get(#name).get()->getString()

/**
 * @def SETV
 * @brief Macro for making setting variable value easier.
 * @param name Name of the variable to set.
 * @param value New value to set.
 * 
 * Sets value of variable of name @p name.
 * @code
 * SETV(foo, 15);
 * @endcode
 */
#define SETV(name, value) EngineVariables::get(#name).get()->set(value)

/**
 * @def SETVF
 * @brief Macro for making setting variable value easier.
 * @param name Name of the variable to set.
 * @param value New value to set.
 * 
 * Sets value of variable of name @p name, forcing its callback to run (if exists).
 * @code
 * SETVF(foo, 15);
 * @endcode
 */
#define SETVF(name, value) EngineVariables::get(#name).get()->set(value, true)

/**
 * @}
 */