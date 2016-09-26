/* --------------------------------------------------------------------------------
 #
 #	4DPlugin.cpp
 #	source generated by 4D Plugin Wizard
 #	Project : Simple PostgreSQL Client
 #	author : miyako
 #	2016/09/26
 #
 # --------------------------------------------------------------------------------*/


#include "4DPluginAPI.h"
#include "4DPlugin.h"

void PluginMain(PA_long32 selector, PA_PluginParameters params)
{
	try
	{
		PA_long32 pProcNum = selector;
		sLONG_PTR *pResult = (sLONG_PTR *)params->fResult;
		PackagePtr pParams = (PackagePtr)params->fParameters;

		CommandDispatcher(pProcNum, pResult, pParams); 
	}
	catch(...)
	{

	}
}

void CommandDispatcher (PA_long32 pProcNum, sLONG_PTR *pResult, PackagePtr pParams)
{
	switch(pProcNum)
	{
// --- Simple PostgreSQL Client

		case 1 :
			PQ_EXECUTE(pResult, pParams);
			break;

	}
}

// --------------------------- Simple PostgreSQL Client ---------------------------

void appendString(std::wstring &p, ARRAY_TEXT &t)
{
#if VERSIONWIN
	t.appendUTF16String((const PA_Unichar *)p.c_str(), (uint32_t)p.length());
#else
	uint32_t dataSize = (p.length() * sizeof(wchar_t))+ sizeof(PA_Unichar);
	std::vector<char> buf(dataSize);
	
	uint32_t len = PA_ConvertCharsetToCharset((char *)p.c_str(),
																						p.length() * sizeof(wchar_t),
																						eVTC_UTF_32,
																						(char *)&buf[0],
																						dataSize,
																						eVTC_UTF_16);
	
	t.appendUTF16String((const PA_Unichar *)&buf[0], len);
#endif
}

void copyString(C_TEXT &t, std::wstring &p)
{
#if VERSIONWIN
	p = std::wstring((wchar_t *)t.getUTF16StringPtr());
#else
	
	uint32_t dataSize = (t.getUTF16Length() * sizeof(wchar_t))+ sizeof(wchar_t);
	std::vector<char> buf(dataSize);
	
	PA_ConvertCharsetToCharset((char *)t.getUTF16StringPtr(),
														 t.getUTF16Length() * sizeof(PA_Unichar),
														 eVTC_UTF_16,
														 (char *)&buf[0],
														 dataSize,
														 eVTC_UTF_32);
	
	p = std::wstring((wchar_t *)&buf[0]);
#endif
}

#pragma mark -

void PQ_EXECUTE(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1_connectdb;
	C_TEXT Param2_command;
	ARRAY_TEXT Param3_result;
	ARRAY_TEXT Param4_values;
	C_LONGINT Param5_format;
	C_TEXT returnValue;
	
	Param1_connectdb.fromParamAtIndex(pParams, 1);
	Param2_command.fromParamAtIndex(pParams, 2);
	Param4_values.fromParamAtIndex(pParams, 4);
	Param5_format.fromParamAtIndex(pParams, 5);
	
	CUTF8String connectdb, command, errorMessage;
	Param1_connectdb.copyUTF8String(&connectdb);
	
	PGconn *conn = PQconnectdb((const char *)connectdb.c_str());
	
	unsigned int paramCount = Param4_values.getSize();
	bool useParams = (paramCount > 1);
	
	if(PQstatus(conn) == CONNECTION_OK)
	{
		Param2_command.copyUTF8String(&command);
		PGresult *result;
		
		if(!useParams)
		{
//			result = PQexec(conn, (const char *)command.c_str());
				result = PQexecParams(conn,
															(const char *)command.c_str(),
															0,
															NULL,
															NULL,
															NULL,
															NULL,
															Param5_format.getIntValue());
		}else{
			
			std::vector<char *> paramValues;
			std::vector<int> paramLengths;
			
			std::vector<Oid> paramTypes;
			std::vector<int> paramFormats;
			
			std::vector<CUTF8String> paramStringValues;
//			std::vector<C_BLOB> paramBinaryValues;
			
			for(unsigned int i = 1; i < paramCount; ++i)
			{
				paramTypes.push_back(0);
				paramFormats.push_back(0);
				
//				if(paramFormat == 0)
//				{
					//text
					CUTF8String u;
					Param4_values.copyUTF8StringAtIndex(&u, i);
					paramStringValues.push_back(u);
					paramValues.push_back((char *)u.c_str());
					paramLengths.push_back(u.size());
//				}else{
					//binary
//					CUTF16String _ut;
//					Param4_values.copyUTF16StringAtIndex(&_ut, i);
//					C_TEXT _t;
//					_t.setUTF16String(&_ut);
//					C_BLOB _b;
//					_b.fromB64Text(&_t);
//					paramBinaryValues.push_back(_b);
//					paramValues.push_back((char *)_b.getBytesPtr());
//					paramLengths.push_back(_b.getBytesLength());
//				}
				
			}
			result = PQexecParams(conn,
									 (const char *)command.c_str(),
									 paramCount-1,
									 &paramTypes[0],
									 &paramValues[0],
									 &paramLengths[0],
									 &paramFormats[0],
									 Param5_format.getIntValue());
		}
		
		switch (PQresultStatus(result))
		{
			case PGRES_EMPTY_QUERY:
			case PGRES_BAD_RESPONSE:
			case PGRES_FATAL_ERROR:
			case PGRES_NONFATAL_ERROR:
				errorMessage = CUTF8String((const uint8_t *)PQerrorMessage(conn));
				returnValue.setUTF8String(&errorMessage);
				break;
				
			case PGRES_TUPLES_OK:
			case PGRES_SINGLE_TUPLE:
				Param3_result.setSize(1);
				{
					int countRows = PQntuples(result);
					int countFields = PQnfields(result);
					for(unsigned int r = 0; r < countRows;++r)
					{
						PA_YieldAbsolute();
						
						JSONNODE *n = json_new(JSON_NODE);
						for(unsigned int c = 0; c < countFields;++c)
						{
							char *fieldName = PQfname(result, c);
							char *fieldValue = PQgetvalue(result, r, c);
							int fieldIsNull = PQgetisnull(result, r, c);
							int fieldLength = PQgetlength(result, r, c);
							int fieldFormat = PQfformat(result, c);
//							Oid fieldType = PQftype(result, c);
//							int fieldModifier = PQfmod(result, c);
							
							std::wstring name;
							C_TEXT nn;
							nn.setUTF8String((const uint8_t *)fieldName, strlen(fieldName));
							copyString(nn, name);

							JSONNODE *node = json_new(JSON_NODE);
							json_set_name(node, name.c_str());

							if(fieldIsNull)
							{
								json_cast(node, JSON_NULL);
							}else{
								switch (fieldFormat)
								{
									case 0:
									{
										//zero indicates textual data representation
										std::wstring value;
										C_TEXT nv;
										nv.setUTF8String((const uint8_t *)fieldValue, fieldLength);
										copyString(nv, value);
										json_cast(node, JSON_STRING);
										json_set_a(node, value.c_str());
									}
										break;
										
									default:
									{
										//one indicates binary representation
										//other codes are reserved for future definition
										json_char *b64data = json_encode64((json_const void *)fieldValue, fieldLength);
										JSONNODE *nnode = json_new(JSON_STRING);
										json_set_name(nnode, L"data");
										json_set_a(nnode, b64data);
										json_push_back(node, nnode);
//										JSONNODE *tnode = json_new(JSON_NUMBER);
//										json_set_name(tnode, L"type");
//										json_set_i(tnode, fieldType);
//										json_push_back(node, tnode);
									}
										break;
								}
							}
							json_push_back(n, node);
						}
						json_char *s = json_write(n);
						std::wstring w = std::wstring(s);
						appendString(w, Param3_result);
						json_free(s);
						json_delete(n);
					}
					PQclear(result);
				}
				break;
				
			case PGRES_COMMAND_OK:
				PQclear(result);
				break;
				
			default:
				break;
		};
		
		PQfinish(conn);
		
	}else{
		errorMessage = CUTF8String((const uint8_t *)PQerrorMessage(conn));
		returnValue.setUTF8String(&errorMessage);
	}

	Param3_result.toParamAtIndex(pParams, 3);
	returnValue.setReturn(pResult);
}

