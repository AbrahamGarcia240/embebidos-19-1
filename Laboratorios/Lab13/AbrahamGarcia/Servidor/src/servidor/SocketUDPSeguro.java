/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package servidor;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author abraham
 */
public class SocketUDPSeguro {
    private byte[]buffer = new byte [65536];
    DatagramSocket sock;
    int numeroDeSecuencia=1;
    
     int puerto;
    public SocketUDPSeguro(int puerto) {
        try {
            this.sock = new DatagramSocket(puerto);
            this.puerto=puerto;
        } catch (SocketException ex) {
            Logger.getLogger(SocketUDPSeguro.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public int getPuerto() {
        return puerto;
    }
    
    public Mensaje recibirPaquete(){
         Mensaje m=new Mensaje();
         while(true){
            try {

                    DatagramPacket reply =  new DatagramPacket(buffer,buffer.length);

                    sock.receive(reply);
                    //System.out.println("Ya recibí "+reply.getLength()+" bytes");


                    double X;
                    double Y;

                    byte[] data = reply.getData();
                    ByteBuffer buf = ByteBuffer.wrap(data);
                    buf.order(ByteOrder.LITTLE_ENDIAN);

                    X= buf.getDouble();
                    Y= buf.getDouble();
                    m.setX(X);
                    m.setY(Y);





                return m;



            } catch (IOException ex) {
                Logger.getLogger(SocketUDPSeguro.class.getName()).log(Level.SEVERE, null, ex);
            }
             m= new Mensaje();
            return m;
         }
    }
    
   
    
    
    public void Responder(String ip, int respuesta){
        
        ByteBuffer buf = ByteBuffer.allocate(4032);
        buf.order(ByteOrder.LITTLE_ENDIAN);
        buf.putInt(respuesta); //Mínimo valor entero
       
        try {
            InetAddress host = InetAddress.getByName(ip);
        
        
        DatagramPacket dp = new DatagramPacket(buf.array() , buf.limit(), host , 7201);
        sock.send(dp);
        } catch (UnknownHostException ex) {
            Logger.getLogger(SocketUDPSeguro.class.getName()).log(Level.SEVERE, null, ex);
          
        } catch (IOException ex) {
            Logger.getLogger(SocketUDPSeguro.class.getName()).log(Level.SEVERE, null, ex);
            
        }
       
           
        
    }
}
