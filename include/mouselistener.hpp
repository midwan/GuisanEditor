#ifndef GCE_ML_HPP
#define GCE_ML_HPP


class GlobalMouseListener : public gcn::MouseListener
{
	private:
	int mx,my;
	bool isDrag,isResize;
	public:
	void mousePressed(gcn::MouseEvent& mouseEvent);
	void mouseDragged(gcn::MouseEvent& mouseEvent);
	void mouseReleased(gcn::MouseEvent& mouseEvent);
	void mouseClicked(gcn::MouseEvent& mouseEvent);
	void mouseMoved(gcn::MouseEvent& mouseEvent);
	void mouseEntered(gcn::MouseEvent& mouseEvent);
	void mouseExited(gcn::MouseEvent& mouseEvent);
	void mouseWheelMovedDown(gcn::MouseEvent& mouseEvent);
	void mouseWheelMovedUp(gcn::MouseEvent& mouseEvent);
};

extern GlobalMouseListener MListener;

#endif // of GCE_ML_HPP

