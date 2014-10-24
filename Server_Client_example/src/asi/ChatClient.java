package asi;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class ChatClient {
	public static String SERVER = "192.168.1.3";
	public static int PORT = 5480;		
	
	public static void main(String[] args) throws UnknownHostException, IOException {
		new ChatClient().connect();
	}
	
	private BufferedReader CreateInput(InputStream in){
		InputStreamReader inputStreamReader = new InputStreamReader(in);
		return new BufferedReader(inputStreamReader);
	}
	
	public void connect() throws UnknownHostException, IOException{
		Socket sc = new Socket(SERVER,PORT);
		System.out.println("connected...");
		BufferedReader consIn = CreateInput(System.in);
		BufferedReader servIn = CreateInput(sc.getInputStream());
		
		OutputStream out = sc.getOutputStream();
		PrintWriter output = new PrintWriter(out);
		
		while(true){
			if(consIn.ready()){
				String mess = consIn.readLine();
				if(mess.equals("//end"))
					break;	
				output.println(mess);
				output.flush();
			}
			if(servIn.ready()){
				String mess  = servIn.readLine();
				System.out.println(mess);
			}
		}
		sc.close();
	}
	
}
