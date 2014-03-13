DiDoIni
=======

用于方便的读写INI文件

下面是个例子:


 try{
 
	 DiDo::CIniFile Settings_Ini("c:\\Settings.ini");

	 Settings_Ini["Hello")]["World")] = "Hello world!";

	 COUT << Settings_Ini["Hello"]("World");
	 
 }
 catch ( int e ){
 
	 switch(e){
		 case DiDo::CIniException::Err_FileName_Cannot_Be_NULL: COUT << "Err_FileName_Cannot_Be_NULL"); break;
		 case DiDo::CIniException::Err_Section_Cannot_Be_NULL: COUT  << "Err_Section_Cannot_Be_NULL");  break;
		 case DiDo::CIniException::Err_Key_Cannot_Be_NULL: COUT      << "Err_Key_Cannot_Be_NULL");      break;
		 default:
			throw e;
	}
	
 }
