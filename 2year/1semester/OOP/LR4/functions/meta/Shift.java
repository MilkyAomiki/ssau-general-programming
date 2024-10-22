package functions.meta;

import functions.Function;

public class Shift implements Function {

    private Function func;
    private double xShift;
    private double yShift;

    public Shift(Function func, double xShift, double yShift) {
        this.func = func;
        this.xShift = xShift;
        this.yShift = yShift;
    }

    @Override
    public double getLeftDomainBorder() {
        return func.getLeftDomainBorder() + xShift;
    }

    @Override
    public double getRightDomainBorder() {
        return func.getRightDomainBorder() + xShift;
    }

    @Override
    public double getFunctionValue(double x) {
        return func.getFunctionValue(x) + yShift;
    }
    
}
