import java.net.Socket;
import java.net.UnknownHostException;
import java.io.IOException;

public class PortProbe {
    public static void main(String[ ] args) {
        if (args.length < 1) {
	    System.err.println("Usage: PortProbe <IP address>");
	    return;
        }
        String host = args[0];
        // port numbers for common services
        int[ ] ports = {
	     7,     // ping
            13,     // daytime
            21,     // ftp
            23,     // telnet
            71,     // finger
            80,     // http
	   119,     // nntp (news)
	   161      // snmp
        };
        // Probe each port.
	Socket sock = null;
        for (int port : ports) {
            try {
                sock = new Socket(host, port);
                System.out.println(host + " listening on port " + port);
            }
            catch(UnknownHostException e) {
                System.err.println(e);
                return;
            }
            catch(IOException e) {
                System.out.println(host + " not listening on port " + port);
            }
	    finally {
		try {
		    if (sock != null) sock.close();
		}
		catch(IOException e) { }
	    }
        }
    }
}
/* output:
   java PortProbe condor.depaul.edu
     condor.depaul.edu not listening on port 7
     condor.depaul.edu not listening on port 13
     condor.depaul.edu listening on port 21
     condor.depaul.edu listening on port 23
     condor.depaul.edu not listening on port 71
     condor.depaul.edu listening on port 80
     condor.depaul.edu not listening on port 119
     condor.depaul.edu not listening on port 161
*/

