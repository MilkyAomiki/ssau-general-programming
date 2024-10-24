package functions.meta;

import functions.Function;

public class Mult implements Function {
    private Function funcLeft;
    private Function funcRight;

    public Mult(Function funcLeft, Function funcRight) {
        this.funcLeft = funcLeft;
        this.funcRight = funcRight;
    }

    @Override
    public double getLeftDomainBorder() {
        return Math.min(funcLeft.getLeftDomainBorder(), funcRight.getLeftDomainBorder());
    }

    @Override
    public double getRightDomainBorder() {
        return Math.min(funcRight.getRightDomainBorder(), funcLeft.getRightDomainBorder());
    }

    @Override
    public double getFunctionValue(double x) {
        return funcLeft.getFunctionValue(x) * funcRight.getFunctionValue(x);
    }
    
}
