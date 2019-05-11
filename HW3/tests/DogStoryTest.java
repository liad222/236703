package tests;

import org.junit.Assert;

import Solution.Given;
import Solution.Then;
import Solution.When;

public class DogStoryTest {
	protected tests.Dog dog;
	@Given("a Dog of age &age")
	public void aDog(Integer age) {
		dog = new tests.Dog(age);
	}
	
	@When("the dog is not taken out for a walk, the number of hours is &hours")
	public void dogNotTakenForAWalk(Integer hours) {
		dog.notTakenForAWalk(hours);
	}
	
	@Then("the house condition is &condition")
	public void theHouseCondition(String condition) {
		Assert.assertEquals(condition, dog.houseCondition());
	}
}
