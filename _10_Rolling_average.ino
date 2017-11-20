int Rolling_Average(int Value)
// Calculates rolling average
// Using Waarde_Array, Rolling_Max
{
  unsigned long Total_Average = 0;
  for (int t = Rolling_Max; t > 0; t--)
  { Rolling_Array[t] = Rolling_Array[t-1];}
  Rolling_Array[0] = Value;
  
  for (int t = 0; t < Rolling_Max; t++)
  {Total_Average = Total_Average + Rolling_Array[t];}
  
  return(Total_Average / Rolling_Max);
}
