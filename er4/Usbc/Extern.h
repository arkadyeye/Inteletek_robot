#if !defined( _EXTERN_H_ )
#define _EXTERN_H_

class ErrorInfo
{
public:
    enum ErrorNumber
    { 
		ERROR_NUMBER_ABSENT = -1
	};

    enum AxisNumber
    { 
		AXIS_NUMBER_ABSENT = -1
	};

	ErrorInfo()
	{
		lNumber        = ERROR_NUMBER_ABSENT;
		cAxis          = AXIS_NUMBER_ABSENT;
		ulReserved1    = ulReserved2 = 0;
		cOptional[ 0 ] = '\0';  
	}

	long lNumber;
	char  cAxis;
	ULONG ulReserved1;
	ULONG ulReserved2;
	TCHAR  cOptional[ 81 ];
};

#endif