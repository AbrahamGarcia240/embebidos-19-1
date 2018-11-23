package servidor;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author abraham
 */
public class Mensaje {
  
    private double X;
    private double Y;
    

    public Mensaje(){};
    public Mensaje( double X, double Y) {
       
        this.X=X;
        this.Y=Y;
    }

    

    public double getX() {
        return X;
    }

    public double getY() {
        return Y;
    }

    public void setX(double X) {
        this.X = X;
    }

    public void setY(double Y) {
        this.Y = Y;
    }

    @Override
    public String toString() {
        return "" + X + "," + Y;
    }   
    
}
