package functions.meta;

import functions.Function;

public class Scale implements Function {
    private Function func;
    private double xScale;
    private double yScale;

    public Scale(Function func, double xScale, double yScale ) {
        this.func = func;
        this.xScale = xScale;
        this.yScale = yScale;
    }

    @Override
    public double getLeftDomainBorder() {
        return xScale * func.getLeftDomainBorder();
    }

    @Override
    public double getRightDomainBorder() {
        return xScale * func.getRightDomainBorder();
    }

    @Override
    public double getFunctionValue(double x) {
        return yScale * func.getFunctionValue(x);
    }
    
}
