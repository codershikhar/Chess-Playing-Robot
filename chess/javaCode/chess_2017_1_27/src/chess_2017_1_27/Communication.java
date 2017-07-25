package chess_2017_1_27;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;

public class Communication 
{
	public static String read() throws IOException, InterruptedException 
	{
		File f1 = new File("P2J");
		while(f1.exists() == false){continue;}
		while(f1.length() < 1){continue;}
		
		FileInputStream f = new FileInputStream("P2J");
	    String str = "";
	    int i = 0;
	    while((i = f.read())!=-1)
	    {  
	    	str += (char)i;
	    }  
//	    System.out.println(str);
	    f.close(); 
	    f1.delete();
	    return str;
	}
	
	public static void write(String s) throws InterruptedException, IOException
	{
			FileOutputStream f = new FileOutputStream("J2P");
			f.write(s.getBytes());
			f.close();
	}
}
