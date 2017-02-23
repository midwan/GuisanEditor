
#ifndef GCE_SLIDER_HPP
#define GCE_SLIDER_HPP


// should extend the actual widget you are wrapping not gcn::Widget

class gceSlider : public gcn::Slider
{
    public:
    void draw(gcn::Graphics *g);
};

#endif // end GCE_SLIDER_HPP

