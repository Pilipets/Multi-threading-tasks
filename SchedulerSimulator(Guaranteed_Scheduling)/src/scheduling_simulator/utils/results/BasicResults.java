package scheduling_simulator.utils.results;

public class BasicResults {
  public String schedulingType;
  public String schedulingName;
  public int compuTime;

  public BasicResults (String schedulingType, String schedulingName, int compuTime) {
    this.schedulingType = schedulingType;
    this.schedulingName = schedulingName;
    this.compuTime = compuTime;
  } 	
}
