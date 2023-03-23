PROGRAM BMICALC;

VAR
  WEIGHT: INTEGER;
  HEIGHT: INTEGER;
  BMI: REAL;

BEGIN
  WEIGHT := 0;
  HEIGHT := 0;
  BMI := 0.0;
  
  WRITE('WHAT IS YOUR WEIGHT (IN POUNDS)');
  READ(WEIGHT);

  WRITE('WHAT IS YOUR HEIGHT (IN INCHES)');
  READ(HEIGHT);
  
  BMI := (703 * WEIGHT) / (HEIGHT * HEIGHT);

  WRITE('YOUR BMI IS');
  WRITE(BMI);
  WRITE('');

  IF BMI > 24.99 THEN
    WRITE('YOU MIGHT BE OVERWEIGHT')
  ELSE
    IF BMI < 18.5 THEN
      WRITE('YOU MIGHT BE UNDERWEIGHT')
    ELSE
      WRITE('YOU HAVE A NORMAL WEIGHT')

END