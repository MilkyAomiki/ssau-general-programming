package functions.meta;

import functions.Function;

public class Composition implements Function {
    private Function funcLeft;
    private Function funcRight;

    public Composition(Function funcLeft, Function funcRight) {
        this.funcLeft = funcLeft;
        this.funcRight = funcRight;
    }

    @Override
    public double getLeftDomainBorder() {
        return funcRight.getLeftDomainBorder();
    }

    @Override
    public double getRightDomainBorder() {
        return funcRight.getRightDomainBorder();
    }

    @Override
    public double getFunctionValue(double x) {
        return funcLeft.getFunctionValue(funcRight.getFunctionValue(x));
    }

}
