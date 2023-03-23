PROGRAM CONVERT1;
VAR
  F: REAL;
  C: REAL;
BEGIN
  READ (F) ;
  IF F < -100 THEN
    BEGIN
  	  WRITE('TEMP IS TOO LOW');
	    WRITE('IS IT REALLY THAT COLD')
    END
  ELSE
    BEGIN
      C := (F - 32.0)*(5.0/9.0);
      WRITE (' FAHRENHEIT= ');
      WRITE (F);
      WRITE (' CELSIUS= ');
      WRITE (C)
    END
END
