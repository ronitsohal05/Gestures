
enum class GestureType {
    Pinch,
    Swipe
};

class GestureMapper {
    public:
        GestureMapper();
        ~GestureMapper();

        void mapGesture(GestureType gesture);
}