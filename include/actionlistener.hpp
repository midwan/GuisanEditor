#ifndef GCE_ACTIONL_HPP
#define GCE_ACTIONL_HPP

class gceActionListener : public gcn::ActionListener
{
public:
    void action(const gcn::ActionEvent& actionEvent);
};

extern gceActionListener guiListener;

#endif // of GCE_ACTIONL_HPP

