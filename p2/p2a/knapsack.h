// Knapsack class
// Version f08.1

class knapsack
{
   public:
      knapsack(ifstream &fin);
      knapsack(const knapsack &);
      int getCost(int) const;
      int getValue(int) const;
      int getCost() const;
      int getValue() const;
      int getNumObjects() const;
      int getCostLimit() const;
      void printSolution();
      void select(int);
      void unSelect(int);
      bool isSelected(int) const;
      void unSelectAll();
      vector <float> getVector(int i);

   private:
      int numObjects;
      int costLimit;
      vector<float> index;
      vector<float> value;
      vector<float> cost;
      vector<float> ratio;
      vector<bool> selected;
      matrix<float> data;
      int totalValue;
      int totalCost;
};

knapsack::knapsack(ifstream &fin)
// Construct a new knapsack instance using the data in fin.
{
   int n, b, j;
   float v, c;
   
   fin >> n;  // read the number of objects
   fin >> b;  // read the cost limit

   numObjects = n;
   costLimit = b;
   
   index.resize(n);
   value.resize(n);
   cost.resize(n);
   ratio.resize(n);
   selected.resize(n);
   
   for (int i = 0; i < n; i++)
   {
      fin >> j >> v >> c;
      index[j] = j;
      value[j] = v;
      cost[j] = c;
      float rat = v / c;
      ratio[j] = v / c;
      cout << "ratio for item " << j << " is " << rat << endl;
      unSelect(j);
   }

   data.populateWithVectors(index, ratio);
   data.sortByRatio();
   cout << data << endl;
   totalValue = 0;
   totalCost = 0;
}

knapsack::knapsack(const knapsack &k)
// Knapsack copy constructor.
{
   int n = k.getNumObjects();
   
   value.resize(n);
   cost.resize(n);
   selected.resize(n);
   numObjects = k.getNumObjects();
   costLimit = k.getCostLimit();

   totalCost = 0;
   totalValue = 0;

   for (int i = 0; i < n; i++)
   {
      value[i] = k.getValue(i);
      cost[i] = k.getCost(i);
      if (k.isSelected(i))
	 select(i);
      else
	 unSelect(i);
   }
}

int knapsack::getNumObjects() const
{
   return numObjects;
}

int knapsack::getCostLimit() const
{
   return costLimit;
}


int knapsack::getValue(int i) const
// Return the value of the ith object.
{
   if (i < 0 || i >= getNumObjects())
      throw rangeError("Bad value in knapsack::getValue");
   
   return value[i];
}

int knapsack::getCost(int i) const
// Return the cost of the ith object.
{
   if (i < 0 || i >= getNumObjects())
      throw rangeError("Bad value in knapsack::getCost");

   return cost[i];
}

int knapsack::getCost() const
// Return the cost of the selected objects.
{
   return totalCost;
}

int knapsack::getValue() const
// Return the value of the selected objects.
{
   return totalValue;
}

ostream &operator<<(ostream &ostr, const knapsack &k)
// Print all information about the knapsack.
{
   cout << "------------------------------------------------" << endl;
   cout << "Num objects: " << k.getNumObjects() << " Cost Limit: " << k.getCostLimit() << endl;

   int totalValue = 0;
   int totalCost = 0;
   
   for (int i = 0; i < k.getNumObjects(); i++)
   {
      totalValue += k.getValue(i);
      totalCost += k.getCost(i);
   }

   cout << "Total value: " << totalValue << endl;
   cout << "Total cost: " << totalCost << endl << endl;

   for (int i = 0; i < k.getNumObjects(); i++)
      cout << i << "  " << k.getValue(i) << " " << k.getCost(i) << endl;

   cout << endl;

   return ostr;
}

void knapsack::printSolution()
// Prints out the solution.
{
   cout << "------------------------------------------------" << endl;

   cout << "Total value: " << getValue() << endl;
   cout << "Total cost: " << getCost() << endl << endl;

   // Print out objects in the solution
   for (int i = 0; i < getNumObjects(); i++)
      if (isSelected(i))
	 cout << i << "  " << getValue(i) << " " << getCost(i) << endl;

   cout << endl;

   ofstream outputFile;
   numObjects = getNumObjects();
   outputFile.open("output/knapsack"+to_string(numObjects)+".output");
   outputFile << "Total value: " << getValue() << endl;
   outputFile << "Total cost: " << getCost() << endl << endl;
   for (int i = 0; i < getNumObjects(); i++)
      if (isSelected(i))
	 outputFile << i << "  " << getValue(i) << " " << getCost(i) << endl;

   outputFile << endl;
   outputFile.close();
}

ostream &operator<<(ostream &ostr, vector<bool> v)
// Overloaded output operator for vectors.
{
   for (int i = 0; i < v.size(); i++)
      cout << v[i] << endl;

   return ostr;
}

void knapsack::select(int i)
// Select object i.
{
   if (i < 0 || i >= getNumObjects())
      throw rangeError("Bad value in knapsack::Select");

   if (selected[i] == false)
   {
      selected[i] = true;
      totalCost = totalCost + getCost(i);
      totalValue = totalValue + getValue(i);
      /* out << "adding item " << i << " to knapsack " << endl;
      cout << "the total value of the knapsack is now " << totalValue << endl << endl;
 */   }
}

void knapsack::unSelect(int i)
// unSelect object i.
{
   if (i < 0 || i >= getNumObjects())
      throw rangeError("Bad value in knapsack::unSelect");

   if (selected[i] == true)
   {
      selected[i] = false;
      totalCost = totalCost - getCost(i);
      totalValue = totalValue - getValue(i);
      /* cout << "removing item " << i << " to knapsack " << endl;
      cout << "the total value of the knapsack is now " << totalValue << endl << endl;
 */
   }
}

bool knapsack::isSelected(int i) const
// Return true if object i is currently selected, and false otherwise.
{
   if (i < 0 || i >= getNumObjects())
      throw rangeError("Bad value in knapsack::getValue");

   return selected[i];
}

void knapsack::unSelectAll()
{
      for(int i = 0; i < getNumObjects(); i++)
      {
            if (isSelected(i))
                  unSelect(i);
      }
}

vector <float> knapsack::getVector(int i)
{
      return data[i];
}
