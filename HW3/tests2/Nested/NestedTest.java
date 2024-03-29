package tests.Nested;

import Solution.Given;
import Solution.Then;
import Solution.When;
import org.junit.Assert;

public class NestedTest {
    protected Calculator calculator;

    @Given("number &num")
    private void initNumber(Integer num) {
        calculator = new Calculator(num);
    }

    @When("level0 add &num")
    private void addNum(Integer num) {
        this.calculator.addNum(num);
    }

    @Then("result &num")
    private void areEqualNums(Integer num) {
        Assert.assertEquals(calculator.getNum().toString(), num.toString());
    }
}
