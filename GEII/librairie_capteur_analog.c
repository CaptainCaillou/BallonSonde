
double laDroite(double V)
{
	
	//Information de la thermistance
	return (V - 1.4376)/(-0.0402);
 
}
double laPression(double V)
{

	return ((V/5)+0.04)/0.004;
}

float conversionCTN(int var_temperature)
{
	//références
	double Rref = 68000.0;
	double V_IN = 3.3;

	float V =  (float)var_temperature / 256 * V_IN;
	double Rth = (68000 * V ) / (V_IN - V); //68kOhms
	
	return laDroite(V);
}

float conversionMPX(int var_pression)
{
	double Rref = 68000.0;
	double V_IN = 3.3;

	float V =  (float)var_pression / 256 * V_IN;

	return laPression(V);
}