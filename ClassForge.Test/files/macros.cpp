#define Author_Macro author=$STR_RHS_AUTHOR_FULL;

#define era_am(num) 	class era_##num##_source: era_1_source\
			{\
			hitpoint = era_##num##_hitpoint; \
			};

#define era_hp_de(num) class era_##num##_hitpoint\
			{\
			armor = 1; \
			material = -1; \
			name = e##num##; \
			convexComponent = e##num##; \
			passThrough = 0; \
			minimalHit = 0.08; \
			explosionShielding = 0.007; \
			radius = 0.15; \
			visual = ""; \
class DestructionEffects\
				{\
				ammoExplosionEffect = ""; \
class RHS_ERA_Flash\
					{\
					simulation = "particles"; \
					type = RHS_ERA_Flash; \
					position = e##num##mem; \
					intensity = 0.5; \
					interval = 1; \
					lifeTime = 0.006; \
					}; \
class RHS_ERA_Smoke\
					{\
					simulation = "particles"; \
					type = RHS_ERA_Smoke; \
					position = e##num##mem; \
					intensity = 0.1; \
					interval = 1; \
					lifeTime = 0.04; \
					}; \
class RHS_ERA_Shard\
					{\
					simulation = "particles"; \
					type = RHS_ERA_Shard; \
					position = e##num##mem; \
					intensity = 1; \
					interval = 1; \
					lifeTime = 0.03; \
					}; \
				}; \
			};

#define era_hp_de(num) class era_##num##_hitpoint\
			{\
			armor = 1; \
			material = -1; \
			name = e##num##; \
			convexComponent = e##num##; \
			passThrough = 0; \
			minimalHit = 0.08; \
			explosionShielding = 0.007; \
			radius = 0.15; \
			visual = ""; \
class DestructionEffects\
				{\
				ammoExplosionEffect = ""; \
class RHS_ERA_Flash\
					{\
					simulation = "particles"; \
					type = RHS_ERA_Flash; \
					position = e##num##mem; \
					intensity = 0.5; \
					interval = 1; \
					lifeTime = 0.006; \
					}; \
class RHS_ERA_Smoke\
					{\
					simulation = "particles"; \
					type = RHS_ERA_Smoke; \
					position = e##num##mem; \
					intensity = 0.1; \
					interval = 1; \
					lifeTime = 0.04; \
					}; \
class RHS_ERA_Shard\
					{\
					simulation = "particles"; \
					type = RHS_ERA_Shard; \
					position = e##num##mem; \
					intensity = 1; \
					interval = 1; \
					lifeTime = 0.03; \
					}; \
				}; \
			};