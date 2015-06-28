#include "testApp.h"

vector<string> split(const string &str, const string &delim)
{
	vector<string> res;
	
	size_t current = 0;
	size_t found;
	size_t delimlen = delim.size();
	
	while ((found = str.find(delim, current)) != string::npos)
	{
		res.push_back(string(str, current, found - current));
		current = found + delimlen;
	}
	res.push_back(string(str, current, str.size() - current));
	return res;
}

int countStr(const string &str, const string &searchStr)
{
	size_t current = 0;
	size_t found = 0;
	size_t searchStrLen = searchStr.size();

	int count = 0;
	while ((found = str.find(searchStr, current)) != string::npos)
	{
		count++;
		current = found + searchStrLen;
	}
	
	return count;
}

//--------------------------------------------------------------
void testApp::setup()
{
	serial.setup("/dev/cu.usbmodem1411", 9600);
}

//--------------------------------------------------------------
void testApp::update()
{
	unsigned char bytesReturned[64];
	
	memset(bytesReturned, 0, 64);
	
	int read = 0;
	while (true)
	{
		int r = serial.readBytes(bytesReturned, 64);
		if (r < 0)
		{
			break;
		}
		read = r;
	}
	
	if (read > 0)
	{
		string str = ofToString(bytesReturned);
		
		// 改行が含まれていた場合、終端
		if (str.find("\n", 0) != string::npos)
		{
			// 改行後の値を分離する
			vector<string> strs = split(str, "\n");
			
			string res = bufStr + strs[0];
			
			cout << res;

			// すべて含めてコンマが規定数ないと不正
			if (countStr(res, ",") != 5)
			{
				cout << "(fail)";
			}
			cout << endl;
			
			bufStr = "";

			// 改行後の値は次にまわす（バッファにためる）
			if (strs.size() > 1)
			{
				bufStr += strs[1];
			}
		}
		// 改行が含まれていなければバッファにためる
		else
		{
			bufStr += str;
		}
		
		cout << "(" << read << ")" << endl;
	}
	cout << "--------------------" << endl;
}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}