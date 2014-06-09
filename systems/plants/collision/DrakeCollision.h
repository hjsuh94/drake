#ifndef __DrakeCollision_H__
#define __DrakeCollision_H__

//#include <memory>
#include <Eigen/Dense>
#include <Eigen/StdVector>

//#include <iostream>
//#include <stdexcept>
//#include <bitset>

namespace DrakeCollision
{
  enum Shape {
    UNKNOWN,
    BOX,
    SPHERE,
    CYLINDER,
    MESH,
    CAPSULE
  };

  enum ModelType {
    NONE,
    AUTO,
    BULLET
  };

  class Model {
  public:
    virtual void resize(int num_bodies) {};
    
    virtual void addElement(const int body_idx, const int parent_idx, 
			    const Eigen::Matrix4d& T_element_to_link, Shape shape, 
			    const std::vector<double>& params,
			    bool is_static) {};

    virtual bool updateElementsForBody(const int body_idx, 
				       const Eigen::Matrix4d& T_link_to_world) { return false; };
      
    virtual bool setCollisionFilter(const int body_idx, const uint16_t group, 
				    const uint16_t mask) { return false; };

    virtual bool getPointCollision(const int body_idx, 
				   const int body_collision_idx, 
				   Eigen::Vector3d &ptA, Eigen::Vector3d &ptB, 
				   Eigen::Vector3d &normal) { return false; };

    virtual bool getPairwiseCollision(const int bodyA_idx, const int bodyB_idx, 
				      Eigen::MatrixXd& ptsA, Eigen::MatrixXd& ptsB, 
				      Eigen::MatrixXd& normals) { return false; };

    virtual bool getPairwisePointCollision(const int bodyA_idx, const int bodyB_idx, 
					   const int body_collisionA_idx, 
					   Eigen::Vector3d &ptA, Eigen::Vector3d &ptB, 
					   Eigen::Vector3d &normal) { return false; };

    virtual bool getClosestPoints(const int bodyA_idx, const int bodyB_idx,
				  Eigen::Vector3d& ptA, Eigen::Vector3d& ptB, Eigen::Vector3d& normal,
				  double& distance) { return false; };

    virtual bool closestPointsAllBodies(std::vector<int>& bodyA_idx, 
					std::vector<int>& bodyB_idx, 
					Eigen::MatrixXd& ptsA, Eigen::MatrixXd& ptsB,
					Eigen::MatrixXd& normal, 
					Eigen::VectorXd& distance,
					std::vector<int>& bodies_idx) { return false; };

    virtual bool allCollisions(std::vector<int>& bodyA_idx, 
			       std::vector<int>& bodyB_idx, 
			       Eigen::MatrixXd& ptsA, Eigen::MatrixXd& ptsB) { return false; };
                                  
    //
    // Performs raycasting collision detecting (like a LIDAR / laser rangefinder)
    //
    // @param origin Vector3d specifying the position of the ray's origin
    // @param ray_endpoint Vector3d specifying a second point on the ray in world coordinates
    //
    // @retval distance to the first collision, or -1 on no collision
    //
    virtual double collisionRaycast(const Eigen::Vector3d &origin, const Eigen::Vector3d &ray_endpoint) { return -1.0; };
  };

  std::shared_ptr<Model> newModel();

  std::shared_ptr<Model> newModel(ModelType model_type);

/*

  typedef std::bitset<16> bitmask;
  // Constants
  const std::bitset<16> ALL_MASK(std::string(16,'1'));
  const std::bitset<16> NONE_MASK(0);
  const std::bitset<16> DEFAULT_GROUP(1);

  // Forward declarations
  class BulletModel;
  class BulletElement;
  class ResultCollector;

  class noClosestPointsResultException : public std::exception {};

  class badShapeException : public std::exception
  {
    public:
      badShapeException();
      badShapeException(Shape shape);
      virtual const char* what() const throw();
      virtual ~badShapeException() throw() {};
    protected:
      std::string shape_str;
  };

  class zeroRadiusSphereException : public badShapeException
  {
    public:
      virtual const char* what() const throw();
      virtual ~zeroRadiusSphereException() throw() {};
  };

  class unknownShapeException : public badShapeException
  {
    public:
      unknownShapeException(Shape shape) : badShapeException(shape){};
      virtual const char* what() const throw();
      virtual ~unknownShapeException() throw() {};
  };

  class unsupportedShapeException : public badShapeException
  {
    public:
      unsupportedShapeException(Shape shape) : badShapeException(shape){};
      virtual const char* what() const throw();
      virtual ~unsupportedShapeException() throw() {};
  };

  template<typename T> int sgn(T val) {
      return (T(0) < val) - (val < T(0));
  }

  typedef std::shared_ptr< ResultCollector > ResultCollShPtr;

  ResultCollShPtr newResultCollector();
*/
}
#endif

