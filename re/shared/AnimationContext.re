type animationContextType = {
  indexLanding: bool
};

[@bs.module "src/components/animationContext"]
external context: React.Context.t(animationContextType) = "AnimationContext";
