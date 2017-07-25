package chess_2016_12_11;

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
	public static void read() throws IOException, InterruptedException 
	{
		File f1 = new File("P2J");
		while(f1.exists() == false){continue;}
		while(f1.length() < 5){continue;}
		
		FileInputStream f = new FileInputStream("P2J");
	    String str = "";
	    int i = 0;
	    while((i = f.read())!=-1)
	    {  
	    	str += (char)i;
	    }  
	    System.out.println(str);
	    f.close(); 
	    f1.delete();
//		try 
//		{
//			BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
//			PrintWriter writer = new PrintWriter("result.txt", "UTF-8");
//			String s = bufferRead.readLine();
//			while(s.equals("x")==false) 
//			{
//				writer.println(s);
//				s = bufferRead.readLine();
//			}
//			writer.close();
//		} catch(IOException e) {
//			e.printStackTrace();
//		}
	}
	
	public static void write() throws InterruptedException, IOException
	{
			FileOutputStream f = new FileOutputStream("J2P");
			f.write("This is the shit".getBytes());
			f.close();
	}
}
