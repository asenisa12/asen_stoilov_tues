package asi;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.ObjectInputStream.GetField;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.util.Enumeration;

public class ChatServer {
	private static int SERVER_PORT = 5480;
	
	public void GetIpAddress() throws SocketException{
		Enumeration e = NetworkInterface.getNetworkInterfaces();
		
		InetAddress alteraddr = null;
		while(e.hasMoreElements()){
			NetworkInterface networkInterface = (NetworkInterface) e.nextElement();
			Enumeration ee = networkInterface.getInetAddresses();
			while(ee.hasMoreElements()){
				InetAddress iaddr = (InetAddress)ee.nextElement();
				System.out.println(iaddr.getHostAddress());
			}
		}
			
	}
	
	public static void main(String[] args) throws IOException {
		ChatServer chs = new ChatServer();
		chs.run();
		
	}
	
	private class ClientHandler extends Thread{
		private Socket cliSocket;
		public ClientHandler(Socket sc) {
			cliSocket = sc;
		}
		
		@Override
		public void run(){
			try {
				HandleClient();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		private BufferedReader systemInRead(){
			InputStreamReader in = new InputStreamReader(System.in);
			return new BufferedReader(in);
		}
		
		private void HandleClient() throws IOException{
			InputStream in = cliSocket.getInputStream();
			OutputStream out = cliSocket.getOutputStream();
			
			InputStreamReader inputStreamReader = new InputStreamReader(in);
			BufferedReader input = new BufferedReader(inputStreamReader);
			PrintWriter output = new PrintWriter(out);
			
			BufferedReader sysIN = systemInRead();
			String line = "";
			do{
				if(input.ready()){
					line = input.readLine();
					System.out.println("client: "+line);
									
				} 
				if(sysIN.ready()){
					output.println("Server: "+sysIN.readLine());
				}
				output.flush();	
			}while(!line.equals("//end"));
			
			output.close();
		}
	};
	
	public void run() throws IOException{
		InetAddress addr = InetAddress.getByName("192.168.1.3");
		ServerSocket sc = new ServerSocket(SERVER_PORT,5,addr);
		System.out.println("Server started...");
		
		for(int i=0;i<2;i++){
			Socket client =  sc.accept();
			new ClientHandler(client).start();
		}
		
		sc.close();
	}
}
