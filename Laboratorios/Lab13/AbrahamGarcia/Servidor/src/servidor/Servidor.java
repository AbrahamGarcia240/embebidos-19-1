/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package servidor;

import com.teamdev.jxbrowser.*;
import com.teamdev.jxbrowser.chromium.Browser;
import com.teamdev.jxbrowser.chromium.javafx.BrowserView;
import javax.swing.*;
import java.awt.*;
import com.teamdev.jxbrowser.chromium.Browser;
import com.teamdev.jxbrowser.chromium.BrowserCore;
import com.teamdev.jxbrowser.chromium.internal.Environment;
import com.teamdev.jxbrowser.chromium.javafx.BrowserView;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;



/**
 *
 * @author abraham
 */



public class Servidor {
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        int i=0;
        SocketUDPSeguro s= new SocketUDPSeguro(7300);
        
      do{
        
       
       Mensaje m=s.recibirPaquete();
       File file = new File("miau.html"); 
          
        if(file.delete()) 
        { 
            System.out.println("File deleted successfully"); 
        } 
        else
        { 
            System.out.println("Failed to delete the file"); 
        } 
       System.out.println(m.toString());
       s.Responder("192.168.0.3", 1);
       
       String uno="<!DOCTYPE html>\n" +
        "<html>\n" +
        "  <head>\n" +
        "<meta http-equiv=\"refresh\" content=\"5; URL=file:///home/abraham/Documentos/Sistemas%20Embebidos/embebidos-19-1/Laboratorios/Lab13/AbrahamGarcia/Servidor/miau.html\">"+
        "    <meta name='viewport' content='initial-scale=1.0, user-scalable=no' />\n" +
        "    <style type='text/css'>\n" +
        "      html { height: 100% }\n" +
        "      body { height: 100%; margin: 0; padding: 0 }\n" +
        "      #map-canvas { height: 100% }\n" +
        "    </style>\n" +
        "    <script type='text/javascript'\n" +
        "      src='https://maps.googleapis.com/maps/api/js?key=AIzaSyB7J1zsErb9_7jxNu5KU5kIENFObAQEbl0&sensor=false'>\n" +
        "    </script>\n" +
        "    <script type='text/javascript'>\n" +
        "      var map;\n" +
        "      function initialize() {\n" +
        "        var mapOptions = {\n" +
        "          center: new google.maps.LatLng("+m.toString()+"),\n" +
"          zoom: 15\n" +
"        };\n" +
"       \n" +
"        map = new google.maps.Map(document.getElementById('map-canvas'),\n" +
"            mapOptions);\n" +
"         var marker = new google.maps.Marker({\n" +
"          position: new google.maps.LatLng("+m.toString()+"),\n" +
"          map: map,\n" +
"          title: 'Hello World!'\n" +
"        });\n" +
"      }\n" +
"      google.maps.event.addDomListener(window, 'load', initialize);\n" +
"    </script>\n" +
"  </head>\n" +
"  <body>\n" +
"    <div id='map-canvas'/>\n" +
"  </body>\n" +
"</html>";
       
       
        try {
            PrintWriter writer = new PrintWriter("miau.html", "UTF-8");
            writer.print(uno);
            writer.close();
        } catch (FileNotFoundException ex) {
            Logger.getLogger(Servidor.class.getName()).log(Level.SEVERE, null, ex);
        } catch (UnsupportedEncodingException ex) {
            Logger.getLogger(Servidor.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        if(i==0){
            try {
                java.awt.Desktop.getDesktop().browse(java.net.URI.create("file:///home/abraham/Documentos/Sistemas%20Embebidos/embebidos-19-1/Laboratorios/Lab13/AbrahamGarcia/Servidor/miau.html"));
            } catch (IOException ex) {
                Logger.getLogger(Servidor.class.getName()).log(Level.SEVERE, null, ex);
            }
       
        }
       i++;
          

      }while(true);
        
        
    }
    
    
    
    
}
