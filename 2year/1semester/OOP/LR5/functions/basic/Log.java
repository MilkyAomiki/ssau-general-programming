package functions.basic;

import functions.Function;

public class Log implements Function {
    private double base;

    public Log(double base) {
        this.base = base;        
    }

    @Override
    public double getLeftDomainBorder() {
        return -Double.MAX_VALUE;
    }

    @Override
    public double getRightDomainBorder() {
        return Double.MAX_VALUE;
    }

    @Override
    public double getFunctionValue(double x) {
        return Math.log(x) / Math.log(base);
    }
    
}
