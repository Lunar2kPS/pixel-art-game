#pragma once

//NOTE: size is in bytes, count is in element count

class IndexBuffer {
    private:
        unsigned int rendererId;
        unsigned int count;
    public:
        IndexBuffer(const void* data, unsigned int count);
        ~IndexBuffer();

        inline unsigned int getCount() const { return count; }

        void bind() const;
        void unbind() const;
};
