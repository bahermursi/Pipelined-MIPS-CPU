#ifndef MUX_3_H
#define MUX_3_H

class Mux2;
class Buffer3;
class Mux3 {
    
public:
    Mux3(int i) : I0(0), I1(0), I2(0), S(0) {
		idx = i;
    }
    
	void setI0(int i){
		I0 = i;
	}
    void setI1(int i){
        I1 = i;
    }

    void setI2(int i){
        I2 = i;
    }

    void setS(int i){
        S = i;
    }

	void execute();

	void setBuffer3(Buffer3*);

	void setMux2_8(Mux2*);

	void setMux2_9(Mux2*);

private:

	int idx;

    int I0, I1, I2, S;

	Buffer3* buffer3;

	Mux2* mux2_8;

	Mux2* mux2_9;
};

#endif
