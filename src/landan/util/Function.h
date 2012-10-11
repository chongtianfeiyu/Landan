/*********************************
*Class: Function
*Description: Based off of Elbert Mai's (http://www.codeproject.com/script/Membership/View.aspx?mid=2301380) implementation
*of Callbacks (http://www.codeproject.com/KB/cpp/CPPCallback.aspx).
*Modified to support equality and heavily commented to provide easier understanding of what's happening under the hood.
*Author: jkeon
**********************************/

#ifndef _FUNCTION_H_
#define _FUNCTION_H_

//////////////////////////////////////////////////////////////////////
// MACROS ////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

//Creates and Returns a Free Function object. Static functions etc.
#define FREE_FUNCTION(functionPointer) landan::CreateFunctionBuilder(functionPointer).Wrap<functionPointer>()

//Creates and Returns a Member Function object. Functions inside a class.
#define MEMBER_FUNCTION(functionPointer, instancePointer) landan::CreateFunctionBuilder(functionPointer).Wrap<functionPointer>(instancePointer)

//////////////////////////////////////////////////////////////////////
// NAMESPACE /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

namespace landan {

	//////////////////////////////////////////////////////////////////////
	// CLASS DECLARATION /////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	//Declaring a Class called Function which can be of any type. Naturally we want it to be the Function Signature.
	//We're declaring this here so that the Type itself exists but does nothing and we can extend this with Partial Template Specialization later.
	template <typename FunctionSignature>
	class Function;


	//////////////////////////////////////////////////////////////////////
	// GLOBAL EQUALITY CHECKS ////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	template <typename EqualFuncReturnType>
	inline bool operator== (const Function<EqualFuncReturnType> &lhs, const Function<EqualFuncReturnType> &rhs) {
		return ((lhs.functionPointer == rhs.functionPointer) && (lhs.instancePointer == rhs.instancePointer));
	}

	template <typename NotEqualFuncReturnType>
	inline bool operator!= (const Function<NotEqualFuncReturnType> &lhs, const Function<NotEqualFuncReturnType> &rhs) {
		return ((lhs.functionPointer != rhs.functionPointer) || (lhs.instancePointer != rhs.instancePointer));
	}


	//*********************************************************************************************************************************************************************
	//*********************************************************************************************************************************************************************

	//////////////////////////////////////////////////////////////////////
	// FUNCTION: 0 PARAMETER VERSION /////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	//Using Template Partial Specialization we will only allow implementations of a Function class which are typed to be a Function that could have any return type.
	template <typename ReturnType>
	class Function<ReturnType ()> {

	//PUBLIC FUNCTIONS
	public:
		//Default Constructor - To allow for creation with assigning
		inline Function() : functionPointer(0), instancePointer(0) {}

		//Constructor - Set function pointer via initalizer list
		inline Function(ReturnType (*fp)(const void*), const void *ip) : functionPointer(fp), instancePointer(ip) {}

		//Copy Constructor - Set function pointer via initializer list
		inline Function(const Function& other) : functionPointer(other.functionPointer), instancePointer(other.instancePointer) {}

		//Destructor - Simply set function and instance pointer to 0
		inline ~Function() {
			functionPointer = 0;
			instancePointer = 0;
		}

		//Overloading = operator to allow for assignment
		inline Function& operator= (const Function &other) {
			functionPointer = other.functionPointer;
			instancePointer = other.instancePointer;
			return *this;
		}

		//Overloading () operator so we can use this like a Function
		inline ReturnType operator() () const {
			return (*functionPointer)(instancePointer);
		}

		//Safe Bool Idiom - Allows for checking if a Function has a valid functionPointer or not.
		typedef const void* Function::*bool_type;
		inline operator bool_type() const {
			return (functionPointer != 0) ? &Function::instancePointer : 0;
		}

		//Allowing for Equality/InEquality Checks by granting the Global Equality/InEquality Check Functions access to this classes internals via the friend keyword.
		template <typename EqualFuncReturnType>
		friend inline bool operator ==(const Function<EqualFuncReturnType> & lhs, const Function<EqualFuncReturnType> & rhs);
		template<typename NotEqualFuncReturnType>
		friend inline bool operator !=(const Function<NotEqualFuncReturnType> & lhs, const Function<NotEqualFuncReturnType> & rhs);

	//PRIVATE VARIABLES
	private:
		//Stores a Free Function Pointer to the static wrapper function
		ReturnType (*functionPointer)(const void*);
		//Stores an Instance Pointer
		const void *instancePointer;

	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: FREE FUNCTION 0 PARAMETER VERSION ///////////////
	//////////////////////////////////////////////////////////////////////

	//Builds a Free Function
	template <typename ReturnType>
	class FreeFunctionBuilder0 {
	public:
		//Empty Constructor/Destructor
		inline FreeFunctionBuilder0() {}
		inline ~FreeFunctionBuilder0() {}

		//Performs the wrapping from the actual Free Function to the static Free Function Wrapper in this class.
		template<ReturnType (*functionPointer)()>
		inline static Function<ReturnType ()> Wrap() {
			return Function<ReturnType ()>(&FreeFunctionBuilder0::template Wrapper<functionPointer>, 0);
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params
		template<ReturnType (*functionPointer)()>
		inline static ReturnType Wrapper(const void*) {
			return (*functionPointer)();
		}
	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: MEMBER FUNCTION 0 PARAMETER VERSION /////////////
	//////////////////////////////////////////////////////////////////////

	//Builds a Member Function
	template <typename ReturnType, class ClassType>
	class MemberFunctionBuilder0 {
	public:
		//Empty Constructor/Destructor
		inline MemberFunctionBuilder0() {}
		inline ~MemberFunctionBuilder0() {}

		//Performs the wrapping from the actual Member Function to the static Free Function Wrapper in this class. Casts the instance pointer to a const void*
		template<ReturnType (ClassType::*functionPointer)()>
		inline static Function<ReturnType ()> Wrap(ClassType* ip) {
			return Function<ReturnType ()>(&MemberFunctionBuilder0::template Wrapper<functionPointer>, static_cast<const void*>(ip));
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params. Also casts the const void* back to the correct class instance.
		template<ReturnType (ClassType::*functionPointer)()>
		inline static ReturnType Wrapper(const void* ip) {
			ClassType* instancePointer = const_cast<ClassType*>(static_cast<const ClassType*>(ip));
			return (instancePointer->*functionPointer)();
		}

	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: CONST MEMBER FUNCTION 0 PARAMETER VERSION ///////
	//////////////////////////////////////////////////////////////////////

	//Builds a Const Member Function
	template <typename ReturnType, class ClassType>
	class ConstMemberFunctionBuilder0 {
	public:
		//Empty Constructor/Destructor
		inline ConstMemberFunctionBuilder0() {}
		inline ~ConstMemberFunctionBuilder0() {}

		//Performs the wrapping from the actual Const Member Function to the static Free Function Wrapper in this class. Casts the instance pointer to a const void*
		template<ReturnType (ClassType::*functionPointer)() const>
		inline static Function<ReturnType ()> Wrap(ClassType* ip) {
			return Function<ReturnType ()>(&ConstMemberFunctionBuilder0::template Wrapper<functionPointer>, static_cast<const void*>(ip));
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params. Also casts the const void* back to the correct class instance.
		template<ReturnType (ClassType::*functionPointer)() const>
		inline static ReturnType Wrapper(const void* ip) {
			ClassType* instancePointer = const_cast<ClassType*>(static_cast<const ClassType*>(ip));
			return (instancePointer->*functionPointer)();
		}

	};

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: FREE FUNCTION 0 PARAMETER VERSION ////////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType>
	inline FreeFunctionBuilder0<ReturnType> CreateFunctionBuilder(ReturnType (*fp)()) {
		return FreeFunctionBuilder0<ReturnType>();
	}

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: MEMBER FUNCTION 0 PARAMETER VERSION //////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, class ClassType>
	inline MemberFunctionBuilder0<ReturnType, ClassType> CreateFunctionBuilder(ReturnType (ClassType::*fp)()) {
		return MemberFunctionBuilder0<ReturnType, ClassType>();
	}

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: C MEMBER FUNCTION 0 PARAMETER VERSION ////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, class ClassType>
	inline ConstMemberFunctionBuilder0<ReturnType, ClassType> CreateFunctionBuilder(ReturnType (ClassType::*fp)() const) {
		return ConstMemberFunctionBuilder0<ReturnType, ClassType>();
	}

	//*********************************************************************************************************************************************************************
	//*********************************************************************************************************************************************************************

	//////////////////////////////////////////////////////////////////////
	// FUNCTION: 1 PARAMETER VERSION /////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	//Using Template Partial Specialization we will only allow implementations of a Function class which are typed to be a Function that could have any return type.
	template <typename ReturnType, typename Param0>
	class Function<ReturnType (Param0)> {

	//PUBLIC FUNCTIONS
	public:
		//Default Constructor - To allow for creation with assigning
		inline Function() : functionPointer(0), instancePointer(0) {}

		//Constructor - Set function pointer via initalizer list
		inline Function(ReturnType (*fp)(const void*, Param0 p0), const void *ip) : functionPointer(fp), instancePointer(ip) {}

		//Copy Constructor - Set function pointer via initializer list
		inline Function(const Function& other) : functionPointer(other.functionPointer), instancePointer(other.instancePointer) {}

		//Destructor - Simply set function and instance pointer to 0
		inline ~Function() {
			functionPointer = 0;
			instancePointer = 0;
		}

		//Overloading = operator to allow for assignment
		inline Function& operator= (const Function &other) {
			functionPointer = other.functionPointer;
			instancePointer = other.instancePointer;
			return *this;
		}

		//Overloading () operator so we can use this like a Function
		inline ReturnType operator() (Param0 p0) const {
			return (*functionPointer)(instancePointer, p0);
		}

		//Safe Bool Idiom - Allows for checking if a Function has a valid functionPointer or not.
		typedef const void* Function::*bool_type;
		inline operator bool_type() const {
			return (functionPointer != 0) ? &Function::instancePointer : 0;
		}

		//Allowing for Equality/InEquality Checks by granting the Global Equality/InEquality Check Functions access to this classes internals via the friend keyword.
		template <typename EqualFuncReturnType>
		friend inline bool operator ==(const Function<EqualFuncReturnType> & lhs, const Function<EqualFuncReturnType> & rhs);
		template<typename NotEqualFuncReturnType>
		friend inline bool operator !=(const Function<NotEqualFuncReturnType> & lhs, const Function<NotEqualFuncReturnType> & rhs);

	//PRIVATE VARIABLES
	private:
		//Stores a Free Function Pointer to the static wrapper function
		ReturnType (*functionPointer)(const void*, Param0 p0);
		//Stores an Instance Pointer
		const void *instancePointer;

	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: FREE FUNCTION 1 PARAMETER VERSION ///////////////
	//////////////////////////////////////////////////////////////////////

	//Builds a Free Function
	template <typename ReturnType, typename Param0>
	class FreeFunctionBuilder1 {
	public:
		//Empty Constructor/Destructor
		inline FreeFunctionBuilder1() {}
		inline ~FreeFunctionBuilder1() {}

		//Performs the wrapping from the actual Free Function to the static Free Function Wrapper in this class.
		template<ReturnType (*functionPointer)(Param0 p0)>
		inline static Function<ReturnType (Param0)> Wrap() {
			return Function<ReturnType (Param0)>(&FreeFunctionBuilder1::template Wrapper<functionPointer>, 0);
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params
		template<ReturnType (*functionPointer)(Param0 p0)>
		inline static ReturnType Wrapper(const void*, Param0 p0) {
			return (*functionPointer)(p0);
		}
	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: MEMBER FUNCTION 1 PARAMETER VERSION /////////////
	//////////////////////////////////////////////////////////////////////

	//Builds a Member Function
	template <typename ReturnType, class ClassType, typename Param0>
	class MemberFunctionBuilder1 {
	public:
		//Empty Constructor/Destructor
		inline MemberFunctionBuilder1() {}
		inline ~MemberFunctionBuilder1() {}

		//Performs the wrapping from the actual Member Function to the static Free Function Wrapper in this class. Casts the instance pointer to a const void*
		template<ReturnType (ClassType::*functionPointer)(Param0 p0)>
		inline static Function<ReturnType (Param0)> Wrap(ClassType* ip) {
			return Function<ReturnType (Param0)>(&MemberFunctionBuilder1::template Wrapper<functionPointer>, static_cast<const void*>(ip));
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params. Also casts the const void* back to the correct class instance.
		template<ReturnType (ClassType::*functionPointer)(Param0 p0)>
		inline static ReturnType Wrapper(const void* ip, Param0 p0) {
			ClassType* instancePointer = const_cast<ClassType*>(static_cast<const ClassType*>(ip));
			return (instancePointer->*functionPointer)(p0);
		}

	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: CONST MEMBER FUNCTION 1 PARAMETER VERSION ///////
	//////////////////////////////////////////////////////////////////////

	//Builds a Const Member Function
	template <typename ReturnType, class ClassType, typename Param0>
	class ConstMemberFunctionBuilder1 {
	public:
		//Empty Constructor/Destructor
		inline ConstMemberFunctionBuilder1() {}
		inline ~ConstMemberFunctionBuilder1() {}

		//Performs the wrapping from the actual Const Member Function to the static Free Function Wrapper in this class. Casts the instance pointer to a const void*
		template<ReturnType (ClassType::*functionPointer)(Param0 p0) const>
		inline static Function<ReturnType (Param0 p0)> Wrap(ClassType* ip) {
			return Function<ReturnType (Param0 p0)>(&ConstMemberFunctionBuilder1::template Wrapper<functionPointer>, static_cast<const void*>(ip));
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params. Also casts the const void* back to the correct class instance.
		template<ReturnType (ClassType::*functionPointer)(Param0 p0) const>
		inline static ReturnType Wrapper(const void* ip, Param0 p0) {
			ClassType* instancePointer = const_cast<ClassType*>(static_cast<const ClassType*>(ip));
			return (instancePointer->*functionPointer)(p0);
		}

	};

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: FREE FUNCTION 1 PARAMETER VERSION ////////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, typename Param0>
	inline FreeFunctionBuilder1<ReturnType, Param0> CreateFunctionBuilder(ReturnType (*fp)(Param0 p0)) {
		return FreeFunctionBuilder1<ReturnType, Param0>();
	}

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: MEMBER FUNCTION 1 PARAMETER VERSION //////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, class ClassType, typename Param0>
	inline MemberFunctionBuilder1<ReturnType, ClassType, Param0> CreateFunctionBuilder(ReturnType (ClassType::*fp)(Param0 p0)) {
		return MemberFunctionBuilder1<ReturnType, ClassType, Param0>();
	}

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: C MEMBER FUNCTION 1 PARAMETER VERSION ////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, class ClassType, typename Param0>
	inline ConstMemberFunctionBuilder1<ReturnType, ClassType, Param0> CreateFunctionBuilder(ReturnType (ClassType::*fp)(Param0 p0) const) {
		return ConstMemberFunctionBuilder1<ReturnType, ClassType, Param0>();
	}






	//*********************************************************************************************************************************************************************
	//*********************************************************************************************************************************************************************

	//////////////////////////////////////////////////////////////////////
	// FUNCTION: 2 PARAMETER VERSION /////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	//Using Template Partial Specialization we will only allow implementations of a Function class which are typed to be a Function that could have any return type.
	template <typename ReturnType, typename Param0, typename Param1>
	class Function<ReturnType (Param0, Param1)> {

	//PUBLIC FUNCTIONS
	public:
		//Default Constructor - To allow for creation with assigning
		inline Function() : functionPointer(0), instancePointer(0) {}

		//Constructor - Set function pointer via initalizer list
		inline Function(ReturnType (*fp)(const void*, Param0 p0, Param1 p1), const void *ip) : functionPointer(fp), instancePointer(ip) {}

		//Copy Constructor - Set function pointer via initializer list
		inline Function(const Function& other) : functionPointer(other.functionPointer), instancePointer(other.instancePointer) {}

		//Destructor - Simply set function and instance pointer to 0
		inline ~Function() {
			functionPointer = 0;
			instancePointer = 0;
		}

		//Overloading = operator to allow for assignment
		inline Function& operator= (const Function &other) {
			functionPointer = other.functionPointer;
			instancePointer = other.instancePointer;
			return *this;
		}

		//Overloading () operator so we can use this like a Function
		inline ReturnType operator() (Param0 p0, Param1 p1) const {
			return (*functionPointer)(instancePointer, p0, p1);
		}

		//Safe Bool Idiom - Allows for checking if a Function has a valid functionPointer or not.
		typedef const void* Function::*bool_type;
		inline operator bool_type() const {
			return (functionPointer != 0) ? &Function::instancePointer : 0;
		}

		template <typename EqualFuncReturnType>
		friend inline bool operator ==(const Function<EqualFuncReturnType> & lhs, const Function<EqualFuncReturnType> & rhs);
		template<typename NotEqualFuncReturnType>
		friend inline bool operator !=(const Function<NotEqualFuncReturnType> & lhs, const Function<NotEqualFuncReturnType> & rhs);

	//PRIVATE VARIABLES
	private:
		//Stores a Free Function Pointer to the static wrapper function
		ReturnType (*functionPointer)(const void*, Param0 p0, Param1 p1);
		//Stores an Instance Pointer
		const void *instancePointer;

	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: FREE FUNCTION 2 PARAMETER VERSION ///////////////
	//////////////////////////////////////////////////////////////////////

	//Builds a Free Function
	template <typename ReturnType, typename Param0, typename Param1>
	class FreeFunctionBuilder2 {
	public:
		//Empty Constructor/Destructor
		inline FreeFunctionBuilder2() {}
		inline ~FreeFunctionBuilder2() {}

		//Performs the wrapping from the actual Free Function to the static Free Function Wrapper in this class.
		template<ReturnType (*functionPointer)(Param0 p0, Param1 p1)>
		inline static Function<ReturnType (Param0, Param1)> Wrap() {
			return Function<ReturnType (Param0, Param1)>(&FreeFunctionBuilder2::template Wrapper<functionPointer>, 0);
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params
		template<ReturnType (*functionPointer)(Param0 p0, Param1 p1)>
		inline static ReturnType Wrapper(const void*, Param0 p0, Param1 p1) {
			return (*functionPointer)(p0, p1);
		}
	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: MEMBER FUNCTION 2 PARAMETER VERSION /////////////
	//////////////////////////////////////////////////////////////////////

	//Builds a Member Function
	template <typename ReturnType, class ClassType, typename Param0, typename Param1>
	class MemberFunctionBuilder2 {
	public:
		//Empty Constructor/Destructor
		inline MemberFunctionBuilder2() {}
		inline ~MemberFunctionBuilder2() {}

		//Performs the wrapping from the actual Member Function to the static Free Function Wrapper in this class. Casts the instance pointer to a const void*
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1)>
		inline static Function<ReturnType (Param0, Param1)> Wrap(ClassType* ip) {
			return Function<ReturnType (Param0, Param1)>(&MemberFunctionBuilder2::template Wrapper<functionPointer>, static_cast<const void*>(ip));
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params. Also casts the const void* back to the correct class instance.
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1)>
		inline static ReturnType Wrapper(const void* ip, Param0 p0, Param1 p1) {
			ClassType* instancePointer = const_cast<ClassType*>(static_cast<const ClassType*>(ip));
			return (instancePointer->*functionPointer)(p0, p1);
		}

	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: CONST MEMBER FUNCTION 2 PARAMETER VERSION ///////
	//////////////////////////////////////////////////////////////////////

	//Builds a Const Member Function
	template <typename ReturnType, class ClassType, typename Param0, typename Param1>
	class ConstMemberFunctionBuilder2 {
	public:
		//Empty Constructor/Destructor
		inline ConstMemberFunctionBuilder2() {}
		inline ~ConstMemberFunctionBuilder2() {}

		//Performs the wrapping from the actual Const Member Function to the static Free Function Wrapper in this class. Casts the instance pointer to a const void*
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1) const>
		inline static Function<ReturnType (Param0 p0, Param1 p1)> Wrap(ClassType* ip) {
			return Function<ReturnType (Param0 p0, Param1 p1)>(&ConstMemberFunctionBuilder2::template Wrapper<functionPointer>, static_cast<const void*>(ip));
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params. Also casts the const void* back to the correct class instance.
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1) const>
		inline static ReturnType Wrapper(const void* ip, Param0 p0, Param1 p1) {
			ClassType* instancePointer = const_cast<ClassType*>(static_cast<const ClassType*>(ip));
			return (instancePointer->*functionPointer)(p0, p1);
		}

	};

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: FREE FUNCTION 2 PARAMETER VERSION ////////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, typename Param0, typename Param1>
	inline FreeFunctionBuilder2<ReturnType, Param0, Param1> CreateFunctionBuilder(ReturnType (*fp)(Param0 p0, Param1 p1)) {
		return FreeFunctionBuilder2<ReturnType, Param0, Param1>();
	}

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: MEMBER FUNCTION 2 PARAMETER VERSION //////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, class ClassType, typename Param0, typename Param1>
	inline MemberFunctionBuilder2<ReturnType, ClassType, Param0, Param1> CreateFunctionBuilder(ReturnType (ClassType::*fp)(Param0 p0, Param1 p1)) {
		return MemberFunctionBuilder2<ReturnType, ClassType, Param0, Param1>();
	}

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: C MEMBER FUNCTION 2 PARAMETER VERSION ////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, class ClassType, typename Param0, typename Param1>
	inline ConstMemberFunctionBuilder2<ReturnType, ClassType, Param0, Param1> CreateFunctionBuilder(ReturnType (ClassType::*fp)(Param0 p0, Param1 p1) const) {
		return ConstMemberFunctionBuilder2<ReturnType, ClassType, Param0, Param1>();
	}

	//*********************************************************************************************************************************************************************
	//*********************************************************************************************************************************************************************

	//////////////////////////////////////////////////////////////////////
	// FUNCTION: 3 PARAMETER VERSION /////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	//Using Template Partial Specialization we will only allow implementations of a Function class which are typed to be a Function that could have any return type.
	template <typename ReturnType, typename Param0, typename Param1, typename Param2>
	class Function<ReturnType (Param0, Param1, Param2)> {

	//PUBLIC FUNCTIONS
	public:
		//Default Constructor - To allow for creation with assigning
		inline Function() : functionPointer(0), instancePointer(0) {}

		//Constructor - Set function pointer via initalizer list
		inline Function(ReturnType (*fp)(const void*, Param0 p0, Param1 p1, Param2 p2), const void *ip) : functionPointer(fp), instancePointer(ip) {}

		//Copy Constructor - Set function pointer via initializer list
		inline Function(const Function& other) : functionPointer(other.functionPointer), instancePointer(other.instancePointer) {}

		//Destructor - Simply set function and instance pointer to 0
		inline ~Function() {
			functionPointer = 0;
			instancePointer = 0;
		}

		//Overloading = operator to allow for assignment
		inline Function& operator= (const Function &other) {
			functionPointer = other.functionPointer;
			instancePointer = other.instancePointer;
			return *this;
		}

		//Overloading () operator so we can use this like a Function
		inline ReturnType operator() (Param0 p0, Param1 p1, Param2 p2) const {
			return (*functionPointer)(instancePointer, p0, p1, p2);
		}

		//Safe Bool Idiom - Allows for checking if a Function has a valid functionPointer or not.
		typedef const void* Function::*bool_type;
		inline operator bool_type() const {
			return (functionPointer != 0) ? &Function::instancePointer : 0;
		}

		template <typename EqualFuncReturnType>
		friend inline bool operator ==(const Function<EqualFuncReturnType> & lhs, const Function<EqualFuncReturnType> & rhs);
		template<typename NotEqualFuncReturnType>
		friend inline bool operator !=(const Function<NotEqualFuncReturnType> & lhs, const Function<NotEqualFuncReturnType> & rhs);

	//PRIVATE VARIABLES
	private:
		//Stores a Free Function Pointer to the static wrapper function
		ReturnType (*functionPointer)(const void*, Param0 p0, Param1 p1, Param2 p2);
		//Stores an Instance Pointer
		const void *instancePointer;

	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: FREE FUNCTION 3 PARAMETER VERSION ///////////////
	//////////////////////////////////////////////////////////////////////

	//Builds a Free Function
	template <typename ReturnType, typename Param0, typename Param1, typename Param2>
	class FreeFunctionBuilder3 {
	public:
		//Empty Constructor/Destructor
		inline FreeFunctionBuilder3() {}
		inline ~FreeFunctionBuilder3() {}

		//Performs the wrapping from the actual Free Function to the static Free Function Wrapper in this class.
		template<ReturnType (*functionPointer)(Param0 p0, Param1 p1, Param2 p2)>
		inline static Function<ReturnType (Param0, Param1, Param2)> Wrap() {
			return Function<ReturnType (Param0, Param1, Param2)>(&FreeFunctionBuilder3::template Wrapper<functionPointer>, 0);
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params
		template<ReturnType (*functionPointer)(Param0 p0, Param1 p1, Param2 p2)>
		inline static ReturnType Wrapper(const void*, Param0 p0, Param1 p1, Param2 p2) {
			return (*functionPointer)(p0, p1, p2);
		}
	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: MEMBER FUNCTION 3 PARAMETER VERSION /////////////
	//////////////////////////////////////////////////////////////////////

	//Builds a Member Function
	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2>
	class MemberFunctionBuilder3 {
	public:
		//Empty Constructor/Destructor
		inline MemberFunctionBuilder3() {}
		inline ~MemberFunctionBuilder3() {}

		//Performs the wrapping from the actual Member Function to the static Free Function Wrapper in this class. Casts the instance pointer to a const void*
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2)>
		inline static Function<ReturnType (Param0, Param1, Param2)> Wrap(ClassType* ip) {
			return Function<ReturnType (Param0, Param1, Param2)>(&MemberFunctionBuilder3::template Wrapper<functionPointer>, static_cast<const void*>(ip));
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params. Also casts the const void* back to the correct class instance.
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2)>
		inline static ReturnType Wrapper(const void* ip, Param0 p0, Param1 p1, Param2 p2) {
			ClassType* instancePointer = const_cast<ClassType*>(static_cast<const ClassType*>(ip));
			return (instancePointer->*functionPointer)(p0, p1, p2);
		}

	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: CONST MEMBER FUNCTION 3 PARAMETER VERSION ///////
	//////////////////////////////////////////////////////////////////////

	//Builds a Const Member Function
	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2>
	class ConstMemberFunctionBuilder3 {
	public:
		//Empty Constructor/Destructor
		inline ConstMemberFunctionBuilder3() {}
		inline ~ConstMemberFunctionBuilder3() {}

		//Performs the wrapping from the actual Const Member Function to the static Free Function Wrapper in this class. Casts the instance pointer to a const void*
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2) const>
		inline static Function<ReturnType (Param0 p0, Param1 p1, Param2 p2)> Wrap(ClassType* ip) {
			return Function<ReturnType (Param0 p0, Param1 p1, Param2 p2)>(&ConstMemberFunctionBuilder3::template Wrapper<functionPointer>, static_cast<const void*>(ip));
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params. Also casts the const void* back to the correct class instance.
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2) const>
		inline static ReturnType Wrapper(const void* ip, Param0 p0, Param1 p1, Param2 p2) {
			ClassType* instancePointer = const_cast<ClassType*>(static_cast<const ClassType*>(ip));
			return (instancePointer->*functionPointer)(p0, p1, p2);
		}

	};

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: FREE FUNCTION 3 PARAMETER VERSION ////////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, typename Param0, typename Param1, typename Param2>
	inline FreeFunctionBuilder3<ReturnType, Param0, Param1, Param2> CreateFunctionBuilder(ReturnType (*fp)(Param0 p0, Param1 p1, Param2 p2)) {
		return FreeFunctionBuilder3<ReturnType, Param0, Param1, Param2>();
	}

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: MEMBER FUNCTION 3 PARAMETER VERSION //////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2>
	inline MemberFunctionBuilder3<ReturnType, ClassType, Param0, Param1, Param2> CreateFunctionBuilder(ReturnType (ClassType::*fp)(Param0 p0, Param1 p1, Param2 p2)) {
		return MemberFunctionBuilder3<ReturnType, ClassType, Param0, Param1, Param2>();
	}

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: C MEMBER FUNCTION 3 PARAMETER VERSION ////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2>
	inline ConstMemberFunctionBuilder3<ReturnType, ClassType, Param0, Param1, Param2> CreateFunctionBuilder(ReturnType (ClassType::*fp)(Param0 p0, Param1 p1, Param2 p2) const) {
		return ConstMemberFunctionBuilder3<ReturnType, ClassType, Param0, Param1, Param2>();
	}

	//*********************************************************************************************************************************************************************
	//*********************************************************************************************************************************************************************

	//////////////////////////////////////////////////////////////////////
	// FUNCTION: 4 PARAMETER VERSION /////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	//Using Template Partial Specialization we will only allow implementations of a Function class which are typed to be a Function that could have any return type.
	template <typename ReturnType, typename Param0, typename Param1, typename Param2, typename Param3>
	class Function<ReturnType (Param0, Param1, Param2, Param3)> {

	//PUBLIC FUNCTIONS
	public:
		//Default Constructor - To allow for creation with assigning
		inline Function() : functionPointer(0), instancePointer(0) {}

		//Constructor - Set function pointer via initalizer list
		inline Function(ReturnType (*fp)(const void*, Param0 p0, Param1 p1, Param2 p2, Param3 p3), const void *ip) : functionPointer(fp), instancePointer(ip) {}

		//Copy Constructor - Set function pointer via initializer list
		inline Function(const Function& other) : functionPointer(other.functionPointer), instancePointer(other.instancePointer) {}

		//Destructor - Simply set function and instance pointer to 0
		inline ~Function() {
			functionPointer = 0;
			instancePointer = 0;
		}

		//Overloading = operator to allow for assignment
		inline Function& operator= (const Function &other) {
			functionPointer = other.functionPointer;
			instancePointer = other.instancePointer;
			return *this;
		}

		//Overloading () operator so we can use this like a Function
		inline ReturnType operator() (Param0 p0, Param1 p1, Param2 p2, Param3 p3) const {
			return (*functionPointer)(instancePointer, p0, p1, p2, p3);
		}

		//Safe Bool Idiom - Allows for checking if a Function has a valid functionPointer or not.
		typedef const void* Function::*bool_type;
		inline operator bool_type() const {
			return (functionPointer != 0) ? &Function::instancePointer : 0;
		}

		template <typename EqualFuncReturnType>
		friend inline bool operator ==(const Function<EqualFuncReturnType> & lhs, const Function<EqualFuncReturnType> & rhs);
		template<typename NotEqualFuncReturnType>
		friend inline bool operator !=(const Function<NotEqualFuncReturnType> & lhs, const Function<NotEqualFuncReturnType> & rhs);

	//PRIVATE VARIABLES
	private:
		//Stores a Free Function Pointer to the static wrapper function
		ReturnType (*functionPointer)(const void*, Param0 p0, Param1 p1, Param2 p2, Param3 p3);
		//Stores an Instance Pointer
		const void *instancePointer;

	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: FREE FUNCTION 4 PARAMETER VERSION ///////////////
	//////////////////////////////////////////////////////////////////////

	//Builds a Free Function
	template <typename ReturnType, typename Param0, typename Param1, typename Param2, typename Param3>
	class FreeFunctionBuilder4 {
	public:
		//Empty Constructor/Destructor
		inline FreeFunctionBuilder4() {}
		inline ~FreeFunctionBuilder4() {}

		//Performs the wrapping from the actual Free Function to the static Free Function Wrapper in this class.
		template<ReturnType (*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3)>
		inline static Function<ReturnType (Param0, Param1, Param2, Param3)> Wrap() {
			return Function<ReturnType (Param0, Param1, Param2, Param3)>(&FreeFunctionBuilder4::template Wrapper<functionPointer>, 0);
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params
		template<ReturnType (*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3)>
		inline static ReturnType Wrapper(const void*, Param0 p0, Param1 p1, Param2 p2, Param3 p3) {
			return (*functionPointer)(p0, p1, p2, p3);
		}
	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: MEMBER FUNCTION 4 PARAMETER VERSION /////////////
	//////////////////////////////////////////////////////////////////////

	//Builds a Member Function
	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2, typename Param3>
	class MemberFunctionBuilder4 {
	public:
		//Empty Constructor/Destructor
		inline MemberFunctionBuilder4() {}
		inline ~MemberFunctionBuilder4() {}

		//Performs the wrapping from the actual Member Function to the static Free Function Wrapper in this class. Casts the instance pointer to a const void*
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3)>
		inline static Function<ReturnType (Param0, Param1, Param2, Param3)> Wrap(ClassType* ip) {
			return Function<ReturnType (Param0, Param1, Param2, Param3)>(&MemberFunctionBuilder4::template Wrapper<functionPointer>, static_cast<const void*>(ip));
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params. Also casts the const void* back to the correct class instance.
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3)>
		inline static ReturnType Wrapper(const void* ip, Param0 p0, Param1 p1, Param2 p2, Param3 p3) {
			ClassType* instancePointer = const_cast<ClassType*>(static_cast<const ClassType*>(ip));
			return (instancePointer->*functionPointer)(p0, p1, p2, p3);
		}

	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: CONST MEMBER FUNCTION 4 PARAMETER VERSION ///////
	//////////////////////////////////////////////////////////////////////

	//Builds a Const Member Function
	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2, typename Param3>
	class ConstMemberFunctionBuilder4 {
	public:
		//Empty Constructor/Destructor
		inline ConstMemberFunctionBuilder4() {}
		inline ~ConstMemberFunctionBuilder4() {}

		//Performs the wrapping from the actual Const Member Function to the static Free Function Wrapper in this class. Casts the instance pointer to a const void*
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3) const>
		inline static Function<ReturnType (Param0 p0, Param1 p1, Param2 p2, Param3 p3)> Wrap(ClassType* ip) {
			return Function<ReturnType (Param0 p0, Param1 p1, Param2 p2, Param3 p3)>(&ConstMemberFunctionBuilder4::template Wrapper<functionPointer>, static_cast<const void*>(ip));
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params. Also casts the const void* back to the correct class instance.
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3) const>
		inline static ReturnType Wrapper(const void* ip, Param0 p0, Param1 p1, Param2 p2, Param3 p3) {
			ClassType* instancePointer = const_cast<ClassType*>(static_cast<const ClassType*>(ip));
			return (instancePointer->*functionPointer)(p0, p1, p2, p3);
		}

	};

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: FREE FUNCTION 4 PARAMETER VERSION ////////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, typename Param0, typename Param1, typename Param2, typename Param3>
	inline FreeFunctionBuilder4<ReturnType, Param0, Param1, Param2, Param3> CreateFunctionBuilder(ReturnType (*fp)(Param0 p0, Param1 p1, Param2 p2, Param3 p3)) {
		return FreeFunctionBuilder4<ReturnType, Param0, Param1, Param2, Param3>();
	}

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: MEMBER FUNCTION 4 PARAMETER VERSION //////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2, typename Param3>
	inline MemberFunctionBuilder4<ReturnType, ClassType, Param0, Param1, Param2, Param3> CreateFunctionBuilder(ReturnType (ClassType::*fp)(Param0 p0, Param1 p1, Param2 p2, Param3 p3)) {
		return MemberFunctionBuilder4<ReturnType, ClassType, Param0, Param1, Param2, Param3>();
	}

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: C MEMBER FUNCTION 4 PARAMETER VERSION ////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2, typename Param3>
	inline ConstMemberFunctionBuilder4<ReturnType, ClassType, Param0, Param1, Param2, Param3> CreateFunctionBuilder(ReturnType (ClassType::*fp)(Param0 p0, Param1 p1, Param2 p2, Param3 p3) const) {
		return ConstMemberFunctionBuilder4<ReturnType, ClassType, Param0, Param1, Param2, Param3>();
	}

	//*********************************************************************************************************************************************************************
	//*********************************************************************************************************************************************************************

	//////////////////////////////////////////////////////////////////////
	// FUNCTION: 5 PARAMETER VERSION /////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	//Using Template Partial Specialization we will only allow implementations of a Function class which are typed to be a Function that could have any return type.
	template <typename ReturnType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4>
	class Function<ReturnType (Param0, Param1, Param2, Param3, Param4)> {

	//PUBLIC FUNCTIONS
	public:
		//Default Constructor - To allow for creation with assigning
		inline Function() : functionPointer(0), instancePointer(0) {}

		//Constructor - Set function pointer via initalizer list
		inline Function(ReturnType (*fp)(const void*, Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4), const void *ip) : functionPointer(fp), instancePointer(ip) {}

		//Copy Constructor - Set function pointer via initializer list
		inline Function(const Function& other) : functionPointer(other.functionPointer), instancePointer(other.instancePointer) {}

		//Destructor - Simply set function and instance pointer to 0
		inline ~Function() {
			functionPointer = 0;
			instancePointer = 0;
		}

		//Overloading = operator to allow for assignment
		inline Function& operator= (const Function &other) {
			functionPointer = other.functionPointer;
			instancePointer = other.instancePointer;
			return *this;
		}

		//Overloading () operator so we can use this like a Function
		inline ReturnType operator() (Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4) const {
			return (*functionPointer)(instancePointer, p0, p1, p2, p3, p4);
		}

		//Safe Bool Idiom - Allows for checking if a Function has a valid functionPointer or not.
		typedef const void* Function::*bool_type;
		inline operator bool_type() const {
			return (functionPointer != 0) ? &Function::instancePointer : 0;
		}

		template <typename EqualFuncReturnType>
		friend inline bool operator ==(const Function<EqualFuncReturnType> & lhs, const Function<EqualFuncReturnType> & rhs);
		template<typename NotEqualFuncReturnType>
		friend inline bool operator !=(const Function<NotEqualFuncReturnType> & lhs, const Function<NotEqualFuncReturnType> & rhs);

	//PRIVATE VARIABLES
	private:
		//Stores a Free Function Pointer to the static wrapper function
		ReturnType (*functionPointer)(const void*, Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4);
		//Stores an Instance Pointer
		const void *instancePointer;

	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: FREE FUNCTION 5 PARAMETER VERSION ///////////////
	//////////////////////////////////////////////////////////////////////

	//Builds a Free Function
	template <typename ReturnType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4>
	class FreeFunctionBuilder5 {
	public:
		//Empty Constructor/Destructor
		inline FreeFunctionBuilder5() {}
		inline ~FreeFunctionBuilder5() {}

		//Performs the wrapping from the actual Free Function to the static Free Function Wrapper in this class.
		template<ReturnType (*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4)>
		inline static Function<ReturnType (Param0, Param1, Param2, Param3, Param4)> Wrap() {
			return Function<ReturnType (Param0, Param1, Param2, Param3, Param4)>(&FreeFunctionBuilder5::template Wrapper<functionPointer>, 0);
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params
		template<ReturnType (*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4)>
		inline static ReturnType Wrapper(const void*, Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4) {
			return (*functionPointer)(p0, p1, p2, p3, p4);
		}
	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: MEMBER FUNCTION 5 PARAMETER VERSION /////////////
	//////////////////////////////////////////////////////////////////////

	//Builds a Member Function
	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4>
	class MemberFunctionBuilder5 {
	public:
		//Empty Constructor/Destructor
		inline MemberFunctionBuilder5() {}
		inline ~MemberFunctionBuilder5() {}

		//Performs the wrapping from the actual Member Function to the static Free Function Wrapper in this class. Casts the instance pointer to a const void*
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4)>
		inline static Function<ReturnType (Param0, Param1, Param2, Param3, Param4)> Wrap(ClassType* ip) {
			return Function<ReturnType (Param0, Param1, Param2, Param3, Param4)>(&MemberFunctionBuilder5::template Wrapper<functionPointer>, static_cast<const void*>(ip));
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params. Also casts the const void* back to the correct class instance.
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4)>
		inline static ReturnType Wrapper(const void* ip, Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4) {
			ClassType* instancePointer = const_cast<ClassType*>(static_cast<const ClassType*>(ip));
			return (instancePointer->*functionPointer)(p0, p1, p2, p3, p4);
		}

	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: CONST MEMBER FUNCTION 5 PARAMETER VERSION ///////
	//////////////////////////////////////////////////////////////////////

	//Builds a Const Member Function
	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4>
	class ConstMemberFunctionBuilder5 {
	public:
		//Empty Constructor/Destructor
		inline ConstMemberFunctionBuilder5() {}
		inline ~ConstMemberFunctionBuilder5() {}

		//Performs the wrapping from the actual Const Member Function to the static Free Function Wrapper in this class. Casts the instance pointer to a const void*
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4) const>
		inline static Function<ReturnType (Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4)> Wrap(ClassType* ip) {
			return Function<ReturnType (Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4)>(&ConstMemberFunctionBuilder5::template Wrapper<functionPointer>, static_cast<const void*>(ip));
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params. Also casts the const void* back to the correct class instance.
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4) const>
		inline static ReturnType Wrapper(const void* ip, Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4) {
			ClassType* instancePointer = const_cast<ClassType*>(static_cast<const ClassType*>(ip));
			return (instancePointer->*functionPointer)(p0, p1, p2, p3, p4);
		}

	};

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: FREE FUNCTION 5 PARAMETER VERSION ////////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4>
	inline FreeFunctionBuilder5<ReturnType, Param0, Param1, Param2, Param3, Param4> CreateFunctionBuilder(ReturnType (*fp)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4)) {
		return FreeFunctionBuilder5<ReturnType, Param0, Param1, Param2, Param3, Param4>();
	}

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: MEMBER FUNCTION 5 PARAMETER VERSION //////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4>
	inline MemberFunctionBuilder5<ReturnType, ClassType, Param0, Param1, Param2, Param3, Param4> CreateFunctionBuilder(ReturnType (ClassType::*fp)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4)) {
		return MemberFunctionBuilder5<ReturnType, ClassType, Param0, Param1, Param2, Param3, Param4>();
	}

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: C MEMBER FUNCTION 5 PARAMETER VERSION ////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4>
	inline ConstMemberFunctionBuilder5<ReturnType, ClassType, Param0, Param1, Param2, Param3, Param4> CreateFunctionBuilder(ReturnType (ClassType::*fp)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4) const) {
		return ConstMemberFunctionBuilder5<ReturnType, ClassType, Param0, Param1, Param2, Param3, Param4>();
	}

	//*********************************************************************************************************************************************************************
	//*********************************************************************************************************************************************************************

	//////////////////////////////////////////////////////////////////////
	// FUNCTION: 6 PARAMETER VERSION /////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	//Using Template Partial Specialization we will only allow implementations of a Function class which are typed to be a Function that could have any return type.
	template <typename ReturnType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	class Function<ReturnType (Param0, Param1, Param2, Param3, Param4, Param5)> {

	//PUBLIC FUNCTIONS
	public:
		//Default Constructor - To allow for creation with assigning
		inline Function() : functionPointer(0), instancePointer(0) {}

		//Constructor - Set function pointer via initalizer list
		inline Function(ReturnType (*fp)(const void*, Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5), const void *ip) : functionPointer(fp), instancePointer(ip) {}

		//Copy Constructor - Set function pointer via initializer list
		inline Function(const Function& other) : functionPointer(other.functionPointer), instancePointer(other.instancePointer) {}

		//Destructor - Simply set function and instance pointer to 0
		inline ~Function() {
			functionPointer = 0;
			instancePointer = 0;
		}

		//Overloading = operator to allow for assignment
		inline Function& operator= (const Function &other) {
			functionPointer = other.functionPointer;
			instancePointer = other.instancePointer;
			return *this;
		}

		//Overloading () operator so we can use this like a Function
		inline ReturnType operator() (Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param4 p5) const {
			return (*functionPointer)(instancePointer, p0, p1, p2, p3, p4, p5);
		}

		//Safe Bool Idiom - Allows for checking if a Function has a valid functionPointer or not.
		typedef const void* Function::*bool_type;
		inline operator bool_type() const {
			return (functionPointer != 0) ? &Function::instancePointer : 0;
		}

		template <typename EqualFuncReturnType>
		friend inline bool operator ==(const Function<EqualFuncReturnType> & lhs, const Function<EqualFuncReturnType> & rhs);
		template<typename NotEqualFuncReturnType>
		friend inline bool operator !=(const Function<NotEqualFuncReturnType> & lhs, const Function<NotEqualFuncReturnType> & rhs);

	//PRIVATE VARIABLES
	private:
		//Stores a Free Function Pointer to the static wrapper function
		ReturnType (*functionPointer)(const void*, Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5);
		//Stores an Instance Pointer
		const void *instancePointer;

	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: FREE FUNCTION 6 PARAMETER VERSION ///////////////
	//////////////////////////////////////////////////////////////////////

	//Builds a Free Function
	template <typename ReturnType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	class FreeFunctionBuilder6 {
	public:
		//Empty Constructor/Destructor
		inline FreeFunctionBuilder6() {}
		inline ~FreeFunctionBuilder6() {}

		//Performs the wrapping from the actual Free Function to the static Free Function Wrapper in this class.
		template<ReturnType (*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)>
		inline static Function<ReturnType (Param0, Param1, Param2, Param3, Param4, Param5)> Wrap() {
			return Function<ReturnType (Param0, Param1, Param2, Param3, Param4, Param5)>(&FreeFunctionBuilder6::template Wrapper<functionPointer>, 0);
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params
		template<ReturnType (*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)>
		inline static ReturnType Wrapper(const void*, Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) {
			return (*functionPointer)(p0, p1, p2, p3, p4, p5);
		}
	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: MEMBER FUNCTION 6 PARAMETER VERSION /////////////
	//////////////////////////////////////////////////////////////////////

	//Builds a Member Function
	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	class MemberFunctionBuilder6 {
	public:
		//Empty Constructor/Destructor
		inline MemberFunctionBuilder6() {}
		inline ~MemberFunctionBuilder6() {}

		//Performs the wrapping from the actual Member Function to the static Free Function Wrapper in this class. Casts the instance pointer to a const void*
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)>
		inline static Function<ReturnType (Param0, Param1, Param2, Param3, Param4, Param5)> Wrap(ClassType* ip) {
			return Function<ReturnType (Param0, Param1, Param2, Param3, Param4, Param5)>(&MemberFunctionBuilder6::template Wrapper<functionPointer>, static_cast<const void*>(ip));
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params. Also casts the const void* back to the correct class instance.
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)>
		inline static ReturnType Wrapper(const void* ip, Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) {
			ClassType* instancePointer = const_cast<ClassType*>(static_cast<const ClassType*>(ip));
			return (instancePointer->*functionPointer)(p0, p1, p2, p3, p4, p5);
		}

	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: CONST MEMBER FUNCTION 6 PARAMETER VERSION ///////
	//////////////////////////////////////////////////////////////////////

	//Builds a Const Member Function
	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	class ConstMemberFunctionBuilder6 {
	public:
		//Empty Constructor/Destructor
		inline ConstMemberFunctionBuilder6() {}
		inline ~ConstMemberFunctionBuilder6() {}

		//Performs the wrapping from the actual Const Member Function to the static Free Function Wrapper in this class. Casts the instance pointer to a const void*
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const>
		inline static Function<ReturnType (Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)> Wrap(ClassType* ip) {
			return Function<ReturnType (Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)>(&ConstMemberFunctionBuilder6::template Wrapper<functionPointer>, static_cast<const void*>(ip));
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params. Also casts the const void* back to the correct class instance.
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const>
		inline static ReturnType Wrapper(const void* ip, Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) {
			ClassType* instancePointer = const_cast<ClassType*>(static_cast<const ClassType*>(ip));
			return (instancePointer->*functionPointer)(p0, p1, p2, p3, p4, p5);
		}

	};

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: FREE FUNCTION 6 PARAMETER VERSION ////////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	inline FreeFunctionBuilder6<ReturnType, Param0, Param1, Param2, Param3, Param4, Param5> CreateFunctionBuilder(ReturnType (*fp)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)) {
		return FreeFunctionBuilder6<ReturnType, Param0, Param1, Param2, Param3, Param4, Param5>();
	}

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: MEMBER FUNCTION 6 PARAMETER VERSION //////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	inline MemberFunctionBuilder6<ReturnType, ClassType, Param0, Param1, Param2, Param3, Param4, Param5> CreateFunctionBuilder(ReturnType (ClassType::*fp)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)) {
		return MemberFunctionBuilder6<ReturnType, ClassType, Param0, Param1, Param2, Param3, Param4, Param5>();
	}

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: C MEMBER FUNCTION 6 PARAMETER VERSION ////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	inline ConstMemberFunctionBuilder6<ReturnType, ClassType, Param0, Param1, Param2, Param3, Param4, Param5> CreateFunctionBuilder(ReturnType (ClassType::*fp)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const) {
		return ConstMemberFunctionBuilder6<ReturnType, ClassType, Param0, Param1, Param2, Param3, Param4, Param5>();
	}

	//*********************************************************************************************************************************************************************
	//*********************************************************************************************************************************************************************

	//////////////////////////////////////////////////////////////////////
	// FUNCTION: 7 PARAMETER VERSION /////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	//Using Template Partial Specialization we will only allow implementations of a Function class which are typed to be a Function that could have any return type.
	template <typename ReturnType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6>
	class Function<ReturnType (Param0, Param1, Param2, Param3, Param4, Param5, Param6)> {

	//PUBLIC FUNCTIONS
	public:
		//Default Constructor - To allow for creation with assigning
		inline Function() : functionPointer(0), instancePointer(0) {}

		//Constructor - Set function pointer via initalizer list
		inline Function(ReturnType (*fp)(const void*, Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6), const void *ip) : functionPointer(fp), instancePointer(ip) {}

		//Copy Constructor - Set function pointer via initializer list
		inline Function(const Function& other) : functionPointer(other.functionPointer), instancePointer(other.instancePointer) {}

		//Destructor - Simply set function and instance pointer to 0
		inline ~Function() {
			functionPointer = 0;
			instancePointer = 0;
		}

		//Overloading = operator to allow for assignment
		inline Function& operator= (const Function &other) {
			functionPointer = other.functionPointer;
			instancePointer = other.instancePointer;
			return *this;
		}

		//Overloading () operator so we can use this like a Function
		inline ReturnType operator() (Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param4 p5, Param6 p6) const {
			return (*functionPointer)(instancePointer, p0, p1, p2, p3, p4, p5, p6);
		}

		//Safe Bool Idiom - Allows for checking if a Function has a valid functionPointer or not.
		typedef const void* Function::*bool_type;
		inline operator bool_type() const {
			return (functionPointer != 0) ? &Function::instancePointer : 0;
		}

		template <typename EqualFuncReturnType>
		friend inline bool operator ==(const Function<EqualFuncReturnType> & lhs, const Function<EqualFuncReturnType> & rhs);
		template<typename NotEqualFuncReturnType>
		friend inline bool operator !=(const Function<NotEqualFuncReturnType> & lhs, const Function<NotEqualFuncReturnType> & rhs);

	//PRIVATE VARIABLES
	private:
		//Stores a Free Function Pointer to the static wrapper function
		ReturnType (*functionPointer)(const void*, Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6);
		//Stores an Instance Pointer
		const void *instancePointer;

	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: FREE FUNCTION 7 PARAMETER VERSION ///////////////
	//////////////////////////////////////////////////////////////////////

	//Builds a Free Function
	template <typename ReturnType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6>
	class FreeFunctionBuilder7 {
	public:
		//Empty Constructor/Destructor
		inline FreeFunctionBuilder7() {}
		inline ~FreeFunctionBuilder7() {}

		//Performs the wrapping from the actual Free Function to the static Free Function Wrapper in this class.
		template<ReturnType (*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6)>
		inline static Function<ReturnType (Param0, Param1, Param2, Param3, Param4, Param5, Param6)> Wrap() {
			return Function<ReturnType (Param0, Param1, Param2, Param3, Param4, Param5, Param6)>(&FreeFunctionBuilder7::template Wrapper<functionPointer>, 0);
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params
		template<ReturnType (*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6)>
		inline static ReturnType Wrapper(const void*, Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) {
			return (*functionPointer)(p0, p1, p2, p3, p4, p5, p6);
		}
	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: MEMBER FUNCTION 7 PARAMETER VERSION /////////////
	//////////////////////////////////////////////////////////////////////

	//Builds a Member Function
	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6>
	class MemberFunctionBuilder7 {
	public:
		//Empty Constructor/Destructor
		inline MemberFunctionBuilder7() {}
		inline ~MemberFunctionBuilder7() {}

		//Performs the wrapping from the actual Member Function to the static Free Function Wrapper in this class. Casts the instance pointer to a const void*
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6)>
		inline static Function<ReturnType (Param0, Param1, Param2, Param3, Param4, Param5, Param6)> Wrap(ClassType* ip) {
			return Function<ReturnType (Param0, Param1, Param2, Param3, Param4, Param5, Param6)>(&MemberFunctionBuilder7::template Wrapper<functionPointer>, static_cast<const void*>(ip));
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params. Also casts the const void* back to the correct class instance.
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6)>
		inline static ReturnType Wrapper(const void* ip, Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) {
			ClassType* instancePointer = const_cast<ClassType*>(static_cast<const ClassType*>(ip));
			return (instancePointer->*functionPointer)(p0, p1, p2, p3, p4, p5, p6);
		}

	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: CONST MEMBER FUNCTION 7 PARAMETER VERSION ///////
	//////////////////////////////////////////////////////////////////////

	//Builds a Const Member Function
	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6>
	class ConstMemberFunctionBuilder7 {
	public:
		//Empty Constructor/Destructor
		inline ConstMemberFunctionBuilder7() {}
		inline ~ConstMemberFunctionBuilder7() {}

		//Performs the wrapping from the actual Const Member Function to the static Free Function Wrapper in this class. Casts the instance pointer to a const void*
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const>
		inline static Function<ReturnType (Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6)> Wrap(ClassType* ip) {
			return Function<ReturnType (Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6)>(&ConstMemberFunctionBuilder7::template Wrapper<functionPointer>, static_cast<const void*>(ip));
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params. Also casts the const void* back to the correct class instance.
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const>
		inline static ReturnType Wrapper(const void* ip, Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) {
			ClassType* instancePointer = const_cast<ClassType*>(static_cast<const ClassType*>(ip));
			return (instancePointer->*functionPointer)(p0, p1, p2, p3, p4, p5, p6);
		}

	};

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: FREE FUNCTION 7 PARAMETER VERSION ////////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6>
	inline FreeFunctionBuilder7<ReturnType, Param0, Param1, Param2, Param3, Param4, Param5, Param6> CreateFunctionBuilder(ReturnType (*fp)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6)) {
		return FreeFunctionBuilder7<ReturnType, Param0, Param1, Param2, Param3, Param4, Param5, Param6>();
	}

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: MEMBER FUNCTION 7 PARAMETER VERSION //////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6>
	inline MemberFunctionBuilder7<ReturnType, ClassType, Param0, Param1, Param2, Param3, Param4, Param5, Param6> CreateFunctionBuilder(ReturnType (ClassType::*fp)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6)) {
		return MemberFunctionBuilder7<ReturnType, ClassType, Param0, Param1, Param2, Param3, Param4, Param5, Param6>();
	}

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: C MEMBER FUNCTION 7 PARAMETER VERSION ////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6>
	inline ConstMemberFunctionBuilder7<ReturnType, ClassType, Param0, Param1, Param2, Param3, Param4, Param5, Param6> CreateFunctionBuilder(ReturnType (ClassType::*fp)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const) {
		return ConstMemberFunctionBuilder7<ReturnType, ClassType, Param0, Param1, Param2, Param3, Param4, Param5, Param6>();
	}

	//*********************************************************************************************************************************************************************
	//*********************************************************************************************************************************************************************

	//////////////////////////////////////////////////////////////////////
	// FUNCTION: 8 PARAMETER VERSION /////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	//Using Template Partial Specialization we will only allow implementations of a Function class which are typed to be a Function that could have any return type.
	template <typename ReturnType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6, typename Param7>
	class Function<ReturnType (Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7)> {

	//PUBLIC FUNCTIONS
	public:
		//Default Constructor - To allow for creation with assigning
		inline Function() : functionPointer(0), instancePointer(0) {}

		//Constructor - Set function pointer via initalizer list
		inline Function(ReturnType (*fp)(const void*, Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7), const void *ip) : functionPointer(fp), instancePointer(ip) {}

		//Copy Constructor - Set function pointer via initializer list
		inline Function(const Function& other) : functionPointer(other.functionPointer), instancePointer(other.instancePointer) {}

		//Destructor - Simply set function and instance pointer to 0
		inline ~Function() {
			functionPointer = 0;
			instancePointer = 0;
		}

		//Overloading = operator to allow for assignment
		inline Function& operator= (const Function &other) {
			functionPointer = other.functionPointer;
			instancePointer = other.instancePointer;
			return *this;
		}

		//Overloading () operator so we can use this like a Function
		inline ReturnType operator() (Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param4 p5, Param6 p6, Param7 p7) const {
			return (*functionPointer)(instancePointer, p0, p1, p2, p3, p4, p5, p6, p7);
		}

		//Safe Bool Idiom - Allows for checking if a Function has a valid functionPointer or not.
		typedef const void* Function::*bool_type;
		inline operator bool_type() const {
			return (functionPointer != 0) ? &Function::instancePointer : 0;
		}

		template <typename EqualFuncReturnType>
		friend inline bool operator ==(const Function<EqualFuncReturnType> & lhs, const Function<EqualFuncReturnType> & rhs);
		template<typename NotEqualFuncReturnType>
		friend inline bool operator !=(const Function<NotEqualFuncReturnType> & lhs, const Function<NotEqualFuncReturnType> & rhs);

	//PRIVATE VARIABLES
	private:
		//Stores a Free Function Pointer to the static wrapper function
		ReturnType (*functionPointer)(const void*, Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7);
		//Stores an Instance Pointer
		const void *instancePointer;

	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: FREE FUNCTION 8 PARAMETER VERSION ///////////////
	//////////////////////////////////////////////////////////////////////

	//Builds a Free Function
	template <typename ReturnType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6, typename Param7>
	class FreeFunctionBuilder8 {
	public:
		//Empty Constructor/Destructor
		inline FreeFunctionBuilder8() {}
		inline ~FreeFunctionBuilder8() {}

		//Performs the wrapping from the actual Free Function to the static Free Function Wrapper in this class.
		template<ReturnType (*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7)>
		inline static Function<ReturnType (Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7)> Wrap() {
			return Function<ReturnType (Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7)>(&FreeFunctionBuilder8::template Wrapper<functionPointer>, 0);
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params
		template<ReturnType (*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7)>
		inline static ReturnType Wrapper(const void*, Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) {
			return (*functionPointer)(p0, p1, p2, p3, p4, p5, p6, p7);
		}
	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: MEMBER FUNCTION 8 PARAMETER VERSION /////////////
	//////////////////////////////////////////////////////////////////////

	//Builds a Member Function
	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6, typename Param7>
	class MemberFunctionBuilder8 {
	public:
		//Empty Constructor/Destructor
		inline MemberFunctionBuilder8() {}
		inline ~MemberFunctionBuilder8() {}

		//Performs the wrapping from the actual Member Function to the static Free Function Wrapper in this class. Casts the instance pointer to a const void*
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7)>
		inline static Function<ReturnType (Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7)> Wrap(ClassType* ip) {
			return Function<ReturnType (Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7)>(&MemberFunctionBuilder8::template Wrapper<functionPointer>, static_cast<const void*>(ip));
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params. Also casts the const void* back to the correct class instance.
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7)>
		inline static ReturnType Wrapper(const void* ip, Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) {
			ClassType* instancePointer = const_cast<ClassType*>(static_cast<const ClassType*>(ip));
			return (instancePointer->*functionPointer)(p0, p1, p2, p3, p4, p5, p6, p7);
		}

	};

	//////////////////////////////////////////////////////////////////////
	// FUNCTION BUILDER: CONST MEMBER FUNCTION 8 PARAMETER VERSION ///////
	//////////////////////////////////////////////////////////////////////

	//Builds a Const Member Function
	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6, typename Param7>
	class ConstMemberFunctionBuilder8 {
	public:
		//Empty Constructor/Destructor
		inline ConstMemberFunctionBuilder8() {}
		inline ~ConstMemberFunctionBuilder8() {}

		//Performs the wrapping from the actual Const Member Function to the static Free Function Wrapper in this class. Casts the instance pointer to a const void*
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) const>
		inline static Function<ReturnType (Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7)> Wrap(ClassType* ip) {
			return Function<ReturnType (Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7)>(&ConstMemberFunctionBuilder8::template Wrapper<functionPointer>, static_cast<const void*>(ip));
		}

	private:
		//Redirects to the functionPointer passed in at compile time via template params. Also casts the const void* back to the correct class instance.
		template<ReturnType (ClassType::*functionPointer)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) const>
		inline static ReturnType Wrapper(const void* ip, Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) {
			ClassType* instancePointer = const_cast<ClassType*>(static_cast<const ClassType*>(ip));
			return (instancePointer->*functionPointer)(p0, p1, p2, p3, p4, p5, p6, p7);
		}

	};

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: FREE FUNCTION 8 PARAMETER VERSION ////////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6, typename Param7>
	inline FreeFunctionBuilder8<ReturnType, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7> CreateFunctionBuilder(ReturnType (*fp)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7)) {
		return FreeFunctionBuilder8<ReturnType, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7>();
	}

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: MEMBER FUNCTION 8 PARAMETER VERSION //////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6, typename Param7>
	inline MemberFunctionBuilder8<ReturnType, ClassType, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7> CreateFunctionBuilder(ReturnType (ClassType::*fp)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7)) {
		return MemberFunctionBuilder8<ReturnType, ClassType, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7>();
	}

	//////////////////////////////////////////////////////////////////////
	// GLOBAL FUNCTION CREATOR: C MEMBER FUNCTION 8 PARAMETER VERSION ////
	//////////////////////////////////////////////////////////////////////

	template <typename ReturnType, class ClassType, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6, typename Param7>
	inline ConstMemberFunctionBuilder8<ReturnType, ClassType, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7> CreateFunctionBuilder(ReturnType (ClassType::*fp)(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) const) {
		return ConstMemberFunctionBuilder8<ReturnType, ClassType, Param0, Param1, Param2, Param3, Param4, Param5, Param6, Param7>();
	}

}
#endif
