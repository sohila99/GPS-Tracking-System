void systick(uint32_t counts)
{
  NVIC_ST_CTRL_R=0; // disable timer
  NVIC_ST_RELOAD_R = counts-1; // delay time is 1 ms or 16000-1 counts
  NVIC_ST_CURRENT_R = 0; // clear current value & flag
  NVIC_ST_CTRL_R=5; // enable timer
  while (NVIC_ST_CTRL_R & 0x10000==0) {}
}
  
