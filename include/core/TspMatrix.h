#pragma once

class TspMatrix {
	private:
		int numVertices;
		int** matrix;

		void clear();

		bool isValidVertex(int vertex) const;

	public:
		TspMatrix();

		~TspMatrix();

		// Block copy constructor and assignment operator to prevent copying
		TspMatrix(const TspMatrix&) = delete;
		TspMatrix& operator=(const TspMatrix&) = delete;

		void allocate(int size);

		void setWeight(int from, int to, int weight);

		int getWeight(int from, int to) const;

		int getNumVertices() const;

		void print() const;
};